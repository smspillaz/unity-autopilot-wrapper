/*
 * displaydiscovery.cpp
 *
 * Keep opening server connections until one fails to determine
 * a safe display number to use
 *
 * See LICENSE.md for Copyright information.
 */

#include <string>
#include <sstream>
#include <stdexcept>

#include "x11_connection.h"
#include "displaydiscovery.h"

namespace uaw = unity::autopilot_wrapper;

int uaw::FindAvailableDisplayNumber (uaw::X11Connection const &conn)
{
    const int MaxConnections = 255;
    int displayNumber = 0;
    bool serverRunningOnDisplay = true;

    while (serverRunningOnDisplay &&
           displayNumber < MaxConnections)
    {
        std::stringstream ss;
        ss << ":" << displayNumber;
        Display *check =
            conn.OpenDisplay (const_cast <char *> (ss.str ().c_str ()));

        if (!check)
            serverRunningOnDisplay = false;
        else
        {
            conn.CloseDisplay (check);
            ++displayNumber;
        }
    }

    if (displayNumber == MaxConnections)
        throw std::runtime_error ("couldn't find a socket "
                                  "to launch on");

    return displayNumber;
}
