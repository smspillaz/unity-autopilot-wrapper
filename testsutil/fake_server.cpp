/*
 * fake_server.cpp
 *
 * A fake application which does nothing but
 * poll its an empty pipe and raise SIGUSR1
 *
 * See LICENSE.md for Copyright information.
 *
 */

#include <stdlib.h>

#include <signal.h>
#include <unistd.h>

void signal (int sig)
{
    exit (0);
}

int main (int argc, char const *argv[])
{
    sighandler_t handler = signal (SIGUSR1, SIG_IGN);

    if (handler == SIG_IGN)
        kill (getppid (), SIGUSR1);

    pause ();

    return 0;
}
