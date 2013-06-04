/*
 * fake_dbus_launch.cpp
 *
 * A fake dbus session bus which outputs fake
 * environment variables that the test harness
 * expects
 *
 * See LICENSE.md for Copyright information.
 */

#include <iostream>
#include <unistd.h>

int main ()
{
    std::cout << "DBUS_SESSION_BUS_ADDRESS=mock" << std::endl;
    std::cout << "DBUS_SESSION_BUS_PID=12345" << std::endl;
    std::cout << "DBUS_SESSION_BUS_WINDOWID=54321" << std::endl;

    pause ();

    return 0;
}
