/*
 * fake_compiz.cpp
 *
 * A fake compiz which does nothing but
 * poll an empty pipe, and output the continue
 * message for the test harness
 *
 * See LICENSE.md for Copyright information.
 */

#include <iostream>
#include <unistd.h>

int main ()
{
    std::cout << "initLauncher-hud" << std::endl;

    pause ();

    return 0;
}
