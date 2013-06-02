/*
 * fake_dbus_launch.cpp
 *
 * A fake dbus session bus which outputs fake
 * environment variables that the test harness
 * expects
 *
 * See LICENSE.md for Copyright information.
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
    std::cout << "DBUS_SESSION_BUS_ADDRESS=mock" << std::endl;
    std::cout << "DBUS_SESSION_BUS_PID=12345" << std::endl;
    std::cout << "DBUS_SESSION_BUS_WINDOWID=54321" << std::endl;

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

    return 0;
}
