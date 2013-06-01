/*
 * pipe.cpp
 *
 * Utility class to create a unix pipe and
 * close it on teardown
 *
 * See LICENSE.md for Copyright information
 */
#include <iostream>
#include <stdexcept>

#include "nonportable_gnu.h"
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>

#include "pipe.h"

namespace uaw = unity::autopilot_wrapper;

uaw::Pipe::Pipe ()
{
    if (pipe2 (mPipe, O_CLOEXEC) == -1)
        throw std::runtime_error (strerror (errno));
}

uaw::Pipe::~Pipe ()
{
    if (mPipe[0] &&
        close (mPipe[0]) == -1)
        std::cerr << "mPipe[0] " << strerror (errno) << std::endl;

    if (mPipe[1] &&
        close (mPipe[1]) == -1)
        std::cerr << "mPipe[0] " << strerror (errno) << std::endl;
}

int uaw::Pipe::ReadEnd () const
{
    return mPipe[0];
}

int & uaw::Pipe::WriteEnd ()
{
    return mPipe [1];
}
