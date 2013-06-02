/*
 * xephyr_wrapper.cpp
 *
 * Strip -logfile and relaunch Xephyr
 *
 * See LICENCE.md for Copyright information.
 */

#include <iostream>
#include <stdexcept>

#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include <signal.h>

#include "locatebinary.h"
#include "launch.h"

namespace uaw = unity::autopilot_wrapper;

pid_t RealXephyr = 0;

void signal_handler (int sig)
{
    switch (sig)
    {
        case SIGINT:
        case SIGTERM:
            if (RealXephyr)
                kill (RealXephyr, sig);
            exit (0);
            break;
        default:
            break;
    }
}

int main (int argc, char **argv)
{
    struct sigaction action;
    action.sa_handler = signal_handler;
    sigemptyset (&action.sa_mask);
    action.sa_flags = SA_RESETHAND;

    if (sigaction (SIGINT, &action, NULL))
        std::cerr << "Failed to set SIGINT signal handler" << std::endl;
    if (sigaction (SIGTERM, &action, NULL))
        std::cerr << "Failed to set SIGTERM signal handler" << std::endl;

    char **argvCopy = (char **) calloc (sizeof (char *), argc);

    memcpy (static_cast <void *> (argvCopy),
            static_cast <void *> (argv),
            sizeof (char *) * argc);

    char   **dest = NULL;
    char   **start = NULL;
    size_t n = 0;

    for (int i = 0; i < argc; ++i)
    {
        if (strcmp (argvCopy[i], "-logfile") == 0)
        {
            dest = &argvCopy[i];

            argvCopy[i] = NULL;
            argvCopy[++i] = NULL;

            if (++i < argc)
                start = &argvCopy[i];

            n = sizeof (char *) * (argc - i);
        }
    }

    if (dest && start && n)
        memmove (dest, start, n);

    RealXephyr = fork ();

    if (RealXephyr == -1)
        throw std::runtime_error (strerror (RealXephyr));

    if (RealXephyr == 0)
    {
        execvpe (uaw::locateBinary ("Xephyr").c_str (),
                 argvCopy, environ);
    }
    else
        return uaw::waitForProcessEnd (RealXephyr);

    free (argvCopy);

    return 0;
}
