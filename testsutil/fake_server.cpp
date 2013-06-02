/*
 * fake_server.cpp
 *
 * A fake application which does nothing but
 * poll its an empty pipe and raise SIGUSR1
 *
 * See LICENSE.md for Copyright information.
 *
 */

#include <stdexcept>
#include <iostream>

#include <stdlib.h>

#include <fcntl.h>
#include <signal.h>
#include <unistd.h>
#include <sys/poll.h>
#include <cstring>
#include <errno.h>

void signal (int sig)
{
    exit (0);
}

int main (int argc, char const *argv[])
{
    sighandler_t handler = signal (SIGUSR1, SIG_IGN);

    if (handler == SIG_IGN)
        kill (getppid (), SIGUSR1);

    int p[2];
    pipe2 (p, O_CLOEXEC);

    /* Repeat arguments and sleep */
    for (int i = 0; i < argc; ++i)
        std::cout << argv[i] << std::endl;

    struct pollfd pfd;

    pfd.events = POLLIN | POLLOUT | POLLHUP;
    pfd.revents = 0;
    pfd.fd = p[0];

    while (1)
    {
        poll (&pfd, 1, -1);

        if (pfd.revents)
        {
            char buf[1024];
            ssize_t amount = read (pfd.fd, static_cast <void *> (buf), 1023);
            if (amount == -1)
                throw std::runtime_error (strerror (errno));
        }
    }

    close (p[0]);
    close (p[1]);
}
