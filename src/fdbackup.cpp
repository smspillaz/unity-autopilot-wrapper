/*
 * fdbackup.cpp
 *
 * Utility class to save file descriptor names and restore them
 * later
 *
 * See LICENSE.md for Copyright information
 */

#include <iostream>
#include <stdexcept>

#include <unistd.h>
#include <errno.h>
#include <string.h>

#include "fdbackup.h"

namespace uaw = unity::autopilot_wrapper;

uaw::FDBackup::FDBackup (int fd) :
    mOriginalFd (fd),
    mBackupFd (0)
{
    mBackupFd = dup (mOriginalFd);

    /* Save original */
    if (mBackupFd == -1)
        throw std::runtime_error (strerror (errno));
}

uaw::FDBackup::~FDBackup ()
{
    /* Redirect backed up fd to old fd location */
    if (mBackupFd &&
        dup2 (mBackupFd, mOriginalFd) == -1)
        std::cerr << "Failed to restore file descriptor "
                  << strerror (errno) << std::endl;
}
