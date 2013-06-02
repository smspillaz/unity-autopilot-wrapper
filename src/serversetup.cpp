/*
 * serversetup.cpp
 *
 * Determine which XServer is meant to be running
 * and configure the XServer object appropriately
 *
 * See LICENSE.md for Copyright information.
 */

#include <xorg/gtest/xorg-gtest.h>

#include "serversetup.h"
#include "environment.h"
#include "locatebinary.h"

namespace xt = xorg::testing;
namespace uaw = unity::autopilot_wrapper;

void uaw::SetupServer (xt::XServer &server,
                       int         displayNumber)
{
    std::stringstream logFile;
    logFile << "/tmp/Autopilot.Xorg.GTest." << displayNumber << ".log";

    server.SetDisplayNumber (displayNumber);
    server.SetOption ("-logfile", logFile.str ());
}

void uaw::CustomizeServer (xt::XServer     &server,
                           uaw::ServerType type)
{
    switch (type)
    {
        case uaw::ServerType::Headless:
            server.SetOption ("-config", DUMMY_CONF_PATH);
            server.SetServerPath (uaw::locateBinary ("Xorg"));
            break;
        case uaw::ServerType::Xephyr:
            server.SetServerPath (uaw::locateBinary ("UnityXephyrWrapper"));
            server.SetOption ("-screen", "1024x768");
            break;
        default:
            break;
    }
}
