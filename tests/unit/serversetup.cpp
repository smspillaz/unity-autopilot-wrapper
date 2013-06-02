/*
 * serversetup.cpp
 *
 * Test that the different server types
 * are set up in an expected manner
 *
 * See LICENSE.md for Copyright information
 */

#include <gtest/gtest.h>

#include <xorg/gtest/xorg-gtest.h>

#include <cstdlib>

#include "serversetup.h"

namespace xt = xorg::testing;
namespace uaw = unity::autopilot_wrapper;

class ServerSetup :
    public ::testing::Test
{
    public:

        ServerSetup ();

        xt::XServer  server;
};

namespace
{
    const int DisplayNumber = 1;
}

ServerSetup::ServerSetup ()
{
}

TEST_F (ServerSetup, DisplayNumberSet)
{
    uaw::SetupServer (server, DisplayNumber);

    EXPECT_EQ (DisplayNumber, server.GetDisplayNumber ());
}

TEST_F (ServerSetup, LogFileSet)
{
    std::string const ExpectedLogFile ("/tmp/Autopilot.Xorg.GTest.1.log");
    uaw::SetupServer (server, DisplayNumber);

    EXPECT_EQ (ExpectedLogFile, server.GetLogFilePath ());
}

TEST_F (ServerSetup, HeadlessServerConfigSet)
{
    std::string const ConfigFile (DUMMY_CONF_PATH);
    uaw::CustomizeServer (server, uaw::ServerType::Headless);

    EXPECT_EQ (ConfigFile, server.GetConfigPath ());
}

TEST_F (ServerSetup, XephyrServerNoConfigSet)
{
    std::string const ConfigFile ("");
    uaw::CustomizeServer (server, uaw::ServerType::Xephyr);

    EXPECT_EQ (ConfigFile, server.GetConfigPath ());
}
