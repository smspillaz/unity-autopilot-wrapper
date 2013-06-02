/*
 * fake_autopilot.cpp
 *
 * If "list" is in its argv, outputs a list
 * of fake tests like autopilot, otherwise
 * exits.
 *
 * See LICENSE.md for Copyright information.
 */

#include <iostream>
#include <cstring>

int main (int argc, char **argv)
{
    for (int i = 0; i < argc; ++i)
    {
        if (strcmp (argv[i], "list") == 0)
        {
            /* Header */
            printf ("\n\n\n");
            printf ("    fake.fake1\n");
            printf ("    fake.fake2\n");
            printf ("    fake.fake3\n");
            printf ("    fake.fake4\n");
            printf ("    fake.fake5\n");
            printf ("    fake.fake6\n");
            printf ("\n\n\n");
        }
    }

    return 0;
}
