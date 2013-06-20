/*
 * environment.cpp
 *
 * Test that the correct environment and processes
 * running are set up for each test scenario
 *
 * See LICENSE.md for Copyright information.
 */

#include <stdexcept>


#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "environment.h"
#include "resizescreen.h"
#include "tmpenv.h"

#include "x11_connection.h"

#include "mock_x11_connection.h"
#include "is_display_number_matcher.h"

#include "uaw_acceptance_tests_config.h"

using ::testing::_;
using ::testing::AtLeast;
using ::testing::Return;
using ::testing::ReturnNull;
using ::testing::Matcher;
using ::testing::MatcherInterface;
using ::testing::MakeMatcher;
using ::testing::MatchResultListener;
using ::testing::StrEq;
using ::testing::ReturnNull;
using ::unity::autopilot_wrapper::matchers::IsDisplayNumber;

namespace uaw = unity::autopilot_wrapper;
namespace uawt = unity::autopilot_wrapper::test;
namespace uawm = unity::autopilot_wrapper::mocks;

namespace
{
    class EnvironmentRAII
    {
        public:

            EnvironmentRAII (testing::Environment *environment) :
                environment (environment)
            {
                environment->SetUp ();
            }

            ~EnvironmentRAII ()
            {
                environment->TearDown ();
            }

            testing::Environment *environment;

        private:

            EnvironmentRAII (EnvironmentRAII const &) = delete;
            EnvironmentRAII (EnvironmentRAII &&) = delete;
            EnvironmentRAII & operator= (EnvironmentRAII const &) = delete;
    };
}

struct _XDisplay
{
};

class UAWEnvironment :
    public ::testing::Test
{
    public:

        UAWEnvironment ();

        void AvailableDisplayNumber (int n)
        {
            EXPECT_CALL (connection, OpenDisplay (_)).Times (AtLeast (0));
            EXPECT_CALL (connection, CloseDisplay (_)).Times (AtLeast (0));

            /* Return NULL for this display once */
            EXPECT_CALL (connection, OpenDisplay (IsDisplayNumber (n)))
                .Times (AtLeast (1))
                .WillOnce (ReturnNull ())
                .WillRepeatedly (Return (&fakeDisplayObject));

            ON_CALL (connection, OpenDisplay (_))
                .WillByDefault (Return (&fakeDisplayObject));
        }

        void ClearDisplayExpectations ()
        {
            char *chars = const_cast <char *> (":1");
            connection.OpenDisplay (chars);
        }

        void NoDisplayNumber ()
        {
            EXPECT_CALL (connection, OpenDisplay (_)).Times (AtLeast (0));
            EXPECT_CALL (connection, CloseDisplay (_)).Times (AtLeast (0));

            /* Always blocked */
            ON_CALL (connection, OpenDisplay (_))
                .WillByDefault (Return (&fakeDisplayObject));
        }

    private:

        uawt::TmpEnv path;
        uawt::TmpEnv dbusSessionBusAddress;
        uawt::TmpEnv dbusSessionBusPid;
        uawt::TmpEnv dbusSessionBusWindow;
        uawt::TmpEnv xdgConfigHome;
        uawt::TmpEnv compizConfigProfile;
        uawt::TmpEnv compizPluginPath;
        uawt::TmpEnv unityLogSeverity;

        XRRScreenSize availableSizes[2];

    protected:

        Display           fakeDisplayObject;

        uawm::MockX11Connection connection;
        uaw::Environment uawEnvironment;
        ::testing::Environment * environment;
};

UAWEnvironment::UAWEnvironment () :
    /* Push environment variables so that
     * we can restore them later */
    path ("PATH", (std::string (uawt::SimpleExecutableDirectory) + ":" +
                   getenv ("PATH")).c_str ()),
    dbusSessionBusAddress ("DBUS_SESSION_BUS_ADDRESS", "a"),
    dbusSessionBusPid ("DBUS_SESSION_BUS_PID", "a"),
    dbusSessionBusWindow ("DBUS_SESSION_BUS_WINDOW", "a"),
    xdgConfigHome ("XDG_CONFIG_HOME", "a"),
    compizConfigProfile ("COMPIZ_CONFIG_PROFILE", "a"),
    compizPluginPath ("COMPIZ_PLUGIN_PATH", "a"),
    unityLogSeverity ("UNITY_LOG_SEVERITY", "a"),
    uawEnvironment (connection),
    environment (&uawEnvironment)
{
    XRRScreenSize sizes[2] =
    {
        {
            0, 0, 0, 0
        },
        {
            uaw::PreferredMinimumWidth,
            uaw::PreferredMinimumHeight,
            0,
            0
        }
    };

    memcpy (availableSizes, sizes, sizeof (XRRScreenSize) * 2);

    uaw::ScreenSizeArray array;
    array.array = availableSizes;
    array.num = 2;

    AvailableDisplayNumber (1);

    /* Set up dummy expectations and behaviour for
     * changing the resolution */
    EXPECT_CALL (connection, GetConfig (_)).Times (AtLeast (0));
    EXPECT_CALL (connection, GetScreenSizes (_)).Times (AtLeast (0));
    EXPECT_CALL (connection, ChangeSizeIndex (_, _, _)).Times (AtLeast (0));

    ON_CALL (connection, GetConfig (_)).WillByDefault (ReturnNull ());
    ON_CALL (connection, GetScreenSizes (_)).WillByDefault (Return (array));
}

TEST_F (UAWEnvironment, ThrowOnNoDisplayFound)
{
    /* Impossible case */
    ClearDisplayExpectations ();
    NoDisplayNumber ();

    Display disp;
    EXPECT_CALL (connection, OpenDisplay (_)).WillRepeatedly (Return (&disp));
    EXPECT_CALL (connection, CloseDisplay (&disp)).WillRepeatedly (Return (0));

    EXPECT_THROW ({
        environment->SetUp ();
    }, std::runtime_error);
}

TEST_F (UAWEnvironment, FindDisplayAndSetEnv)
{
    EnvironmentRAII env (environment);

    EXPECT_THAT (getenv ("DISPLAY"), StrEq (":1"));
}

TEST_F (UAWEnvironment, ChangeScreenSize)
{
    /* Change to preferred size */
    EXPECT_CALL (connection, ChangeSizeIndex (_, _, 1));

    EnvironmentRAII env (environment);
}

TEST_F (UAWEnvironment, DBusSessionBusAddressSetByDBusLaunch)
{
    EnvironmentRAII env (environment);

    EXPECT_THAT (getenv ("DBUS_SESSION_BUS_ADDRESS"), StrEq ("mock"));
}

TEST_F (UAWEnvironment, DBusSessionBusPIDSetByDBusLaunch)
{
    EnvironmentRAII env (environment);

    EXPECT_THAT (getenv ("DBUS_SESSION_BUS_PID"), StrEq ("12345"));
}

TEST_F (UAWEnvironment, DBusSessionBusWindowIDSetByDBusLaunch)
{
    EnvironmentRAII env (environment);

    EXPECT_THAT (getenv ("DBUS_SESSION_BUS_WINDOWID"), StrEq ("54321"));
}

TEST_F (UAWEnvironment, SetNewXDGConfigHome)
{
    uawEnvironment.SetCompizConfigProfileConfigDir ("/mock/path");

    EnvironmentRAII env (environment);

    EXPECT_THAT (getenv ("XDG_CONFIG_HOME"), StrEq ("/mock/path"));
}

TEST_F (UAWEnvironment, SetCompizConfigProfile)
{
    uawEnvironment.SetCompizConfigProfile ("mock");

    EnvironmentRAII env (environment);

    EXPECT_THAT (getenv ("COMPIZ_CONFIG_PROFILE"), StrEq ("mock"));
}

TEST_F (UAWEnvironment, SetCompizPluginPath)
{
    uawEnvironment.SetCompizPluginPath ("/mock/path");

    EnvironmentRAII env (environment);

    EXPECT_THAT (getenv ("COMPIZ_PLUGIN_DIR"), StrEq ("/mock/path"));
}

TEST_F (UAWEnvironment, UnityLogSeverity)
{
    EnvironmentRAII env (environment);

    EXPECT_THAT (getenv ("UNITY_LOG_SEVERITY"), StrEq ("<root>=INFO"));
}
