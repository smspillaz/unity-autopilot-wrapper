/*
 * redirectedfd.cpp
 *
 * Utility class to redirect operations on one
 * file descriptor into another until destruction.
 *
 * See LICENSE.md for Copyright information
 */

#include <stdexcept>
#include <iostream>

#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <fcntl.h>

#include "redirectedfd.h"

namespace uaw = unity::autopilot_wrapper;

uaw::RedirectedFD::RedirectedFD (int from,
                                 int &to) :
    mToFd (to)
{
    /* Make 'to' take the old file descriptor's place */
    if (dup2 (to, from) == -1)
        throw std::runtime_error (strerror (errno));
}

uaw::RedirectedFD::~RedirectedFD ()
{
    if (mToFd &&
        close (mToFd) == -1)
        std::cerr << "Failed to close redirect-to file descriptor "
                  << strerror (errno) << std::endl;

    mToFd = 0;
}
