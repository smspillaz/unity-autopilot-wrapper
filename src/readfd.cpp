/*
 * readfd.cpp
 *
 * Utility function to read a file descriptor for data
 * into a string
 *
 * See LICENSE.md for Copyright information
 */

#include <string>
#include <stdexcept>

#include <unistd.h>
#include <sys/poll.h>
#include <errno.h>
#include <string.h>

#include "readfd.h"

namespace uaw = unity::autopilot_wrapper;

std::string uaw::FdToString (int fd)
{
    std::string output;

    int bufferSize = 4096;
    char buffer[bufferSize];

    ssize_t count = 0;

    do
    {
        struct pollfd pfd;
        pfd.events = POLLIN | POLLERR | POLLHUP;
        pfd.revents = 0;
        pfd.fd = fd;

        /* Check for 10ms if there's anything waiting to be read */
        int nfds = poll (&pfd, 1, 10);

        if (nfds == -1)
            throw std::runtime_error (strerror (errno));

        if (nfds)
        {
            /* Read as much as we have allocated for */
            count = read (fd, static_cast <void *> (buffer), bufferSize - 1);

            /* Something failed, bail */
            if (count == -1)
                throw std::runtime_error (strerror (errno));

            /* Always null-terminate */
            buffer[count] = '\0';

            /* Add it to the output */
            output += buffer;
        }
        else
        {
            /* There's nothing on the pipe, assume EOF */
            count = 0;
        }

        /* Keep going until there's nothing left */
    } while (count != 0);

    return output;
}
