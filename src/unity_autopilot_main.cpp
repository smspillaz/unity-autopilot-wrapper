/*
 * unity_autopilot_main.cpp
 *
 * Set up default unity-autopilot-wrapper
 * test environment
 *
 * See LICENSE.md for Copyright information.
 */

#include <gtest/gtest.h>

#include "environment.h"
#include "x11_connection.h"
#include "concrete_x11_connection.h"

namespace uaw = unity::autopilot_wrapper;

int main (int argc, char **argv)
{
    uaw::ConcreteX11Connection connection;

    ::testing::InitGoogleTest (&argc, argv);
    ::testing::AddGlobalTestEnvironment (new uaw::Environment (connection));

    return RUN_ALL_TESTS ();
}
