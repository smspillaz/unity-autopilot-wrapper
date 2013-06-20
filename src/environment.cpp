/*
 * environment.cpp
 *
 * Set up servers, compiz etc.
 *
 * See LICENSE.md for Copyright information.
 */

#include <memory>
#include <thread>
#include <future>
#include <functional>

#include <boost/algorithm/string.hpp>

#include <sys/types.h>
#include <sys/wait.h>
#include <sys/poll.h>

#include <signal.h>

#include <xorg/gtest/xorg-gtest.h>

#include "displaydiscovery.h"
#include "environment.h"
#include "exports.h"
#include "launch.h"
#include "readfd.h"
#include "resizescreen.h"
#include "locatebinary.h"
#include "pipe.h"
#include "serversetup.h"
#include "x11_connection.h"

namespace uaw = unity::autopilot_wrapper;
namespace xt = xorg::testing;

namespace unity
{
    namespace autopilot_wrapper
    {
        class Environment::Private
        {
            public:

                Private (X11Connection const &);

                std::string  DbusLaunchPath;
                char const **DbusLaunchOptions;

                std::string  CompizPath;
                char const **CompizOptions;
                std::string  CompizPluginPath;
                std::string  CompizConfigProfile;
                std::string  XDGConfigHome;

                std::future <int> DbusLaunchFuture;
                std::future <int> CompizFuture;
                std::future <int> ServerLaunchFuture;

                pid_t DbusLaunch;
                pid_t Compiz;

                uaw::Pipe DbusLaunchStdoutPipe;
                uaw::Pipe CompizStdoutPipe;


                uaw::Pipe DbusLaunchStderrPipe;
                uaw::Pipe CompizStderrPipe;

                ServerType  ServerKind;
                xt::XServer Server;

                uaw::X11Connection const &X11Conn;
        };
    }
}

namespace
{
    char const *NoOptions = NULL;
    char const **GDbusLaunchOptions = &NoOptions;
    char const *GCompizOptions[] =
    {
        "compiz",
        "--replace",
        "ccp"
    };
}

uaw::Environment::Private::Private (X11Connection const &connection) :
    DbusLaunchPath (uaw::locateBinary ("dbus-launch")),
    DbusLaunchOptions (GDbusLaunchOptions),
    CompizPath (uaw::locateBinary ("compiz")),
    CompizOptions (GCompizOptions),
    CompizPluginPath (""),
    CompizConfigProfile ("ubuntu"),
    XDGConfigHome (getenv ("HOME") + std::string ("/.config/")),
    DbusLaunch (0),
    Compiz (0),
    ServerKind (ServerType::Xephyr),
    X11Conn (connection)
{
}

uaw::Environment::Environment (uaw::X11Connection const &connection) :
    priv (new Private (connection))
{
}

void uaw::Environment::SetServerType (ServerType type)
{
    priv->ServerKind = type;
}

void uaw::Environment::SetDbusLaunchPath (std::string const &path)
{
    priv->DbusLaunchPath = path;
}

void uaw::Environment::SetDbusLaunchOptions (char const **options)
{
    priv->DbusLaunchOptions = options;
}

void uaw::Environment::SetCompizPath (std::string const &path)
{
    priv->CompizPath = path;
}

void uaw::Environment::SetCompizOptions (char const **options)
{
    priv->CompizOptions = options;
}

void uaw::Environment::SetCompizPluginPath (std::string const &path)
{
    priv->CompizPluginPath = path;
}

void uaw::Environment::SetCompizConfigProfile (std::string const &profile)
{
    priv->CompizConfigProfile = profile;
}

void uaw::Environment::SetCompizConfigProfileConfigDir (std::string const &dir)
{
    priv->XDGConfigHome = dir;
}

namespace
{
    void WaitUntilUnityRunning (uaw::Pipe const &pipe)
    {
        /* Wait until unity is running */
        size_t      UnityshellStartedPos;
        do
        {
            std::string part = uaw::FdToString (pipe.ReadEnd ());
            UnityshellStartedPos = part.find ("initLauncher-hud");
        } while (UnityshellStartedPos == std::string::npos);
    }
}

void uaw::Environment::SetUp ()
{
    using namespace std::placeholders;
    int displayNumber = uaw::FindAvailableDisplayNumber (priv->X11Conn);

    /* Set up X Server and Launch */
    uaw::SetupServer (priv->Server, displayNumber);
    uaw::CustomizeServer (priv->Server, priv->ServerKind);

    priv->Server.Start ("");
    priv->ServerLaunchFuture =
        std::async (std::launch::async,
                    std::bind (uaw::waitForProcessEnd,
                               priv->Server.Pid ()));

    ExportDisplay (displayNumber);

    Display *dpy = NULL;

    while (!dpy)
    {
        /* Will open the just-exported display string */
        dpy = priv->X11Conn.OpenDisplay (getenv ("DISPLAY"));
    }

    /* Change resolution */
    uaw::ScaleToPreferredMinimum (dpy, priv->X11Conn);

    /* Launch dbus-launch and grab the environment variables that it sets */
    priv->DbusLaunch =
        uaw::launchBinary (priv->DbusLaunchPath,
                           priv->DbusLaunchOptions,
                           priv->DbusLaunchStderrPipe.WriteEnd (),
                           priv->DbusLaunchStdoutPipe.WriteEnd ());

    /* Create a task to allow it to close eventually */
    priv->DbusLaunchFuture =
        std::async (std::launch::async,
                    std::bind (uaw::waitForProcessEnd,
                               priv->DbusLaunch));

    priv->X11Conn.CloseDisplay (dpy);

    std::string DbusLaunchOutput;


    /* Wait until we've found these variables */
    do
    {
        DbusLaunchOutput +=
            uaw::FdToString (priv->DbusLaunchStdoutPipe.ReadEnd ());

    } while (!FindDbusEnvironmentVars (DbusLaunchOutput));

    ExportDbusEnvironmentVars (DbusLaunchOutput);
    ExportUnityEnvironmentVars (priv->XDGConfigHome,
                                priv->CompizConfigProfile,
                                priv->CompizPluginPath);

    priv->Compiz =
        uaw::launchBinary (priv->CompizPath,
                           priv->CompizOptions,
                           priv->CompizStderrPipe.WriteEnd (),
                           priv->CompizStdoutPipe.WriteEnd ());

    /* Create a task to allow it to close eventually */
    priv->CompizFuture =
        std::async (std::launch::async,
                    std::bind (uaw::waitForProcessEnd,
                               priv->Compiz));

    WaitUntilUnityRunning (priv->CompizStdoutPipe);


}

void uaw::Environment::TearDown ()
{
    kill (priv->Compiz, SIGINT);
    priv->CompizFuture.wait ();

    kill (priv->DbusLaunch, SIGINT);
    priv->DbusLaunchFuture.wait ();

    /* We need to send a SIGINT first as it might need
     * to clean up some child processes */
    priv->Server.Terminate ();
    priv->ServerLaunchFuture.wait ();
}
