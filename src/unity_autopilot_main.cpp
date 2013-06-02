/*
 * unity_autopilot_main.cpp
 *
 * Set up default unity-autopilot-wrapper
 * test environment
 *
 * See LICENSE.md for Copyright information.
 */

#include <gtest/gtest.h>

#include <X11/Xlib.h>

#include "environment.h"
#include "x11_connection.h"

namespace uaw = unity::autopilot_wrapper;

namespace
{
    class ConcreteX11Connection :
        public uaw::X11Connection
    {
        public:

            Display * OpenDisplay (char *arg) const
            {
                return XOpenDisplay (arg);
            }

            int CloseDisplay (Display *disp) const
            {
                return XCloseDisplay (disp);
            }
    };
}

int main (int argc, char **argv)
{
    ConcreteX11Connection connection;

    ::testing::InitGoogleTest (&argc, argv);
    ::testing::AddGlobalTestEnvironment (new uaw::Environment (connection));

    return RUN_ALL_TESTS ();
}
