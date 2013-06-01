/*
 * fdbackup.cpp
 *
 * Test backup and restore with dup2
 *
 * See LICENSE.md for Copyright information
 */

#include <memory>
#include <stdexcept>

#include <gtest/gtest.h>

#include <unistd.h>
#include <sys/poll.h>
#include <fcntl.h>
#include <errno.h>

#include "fdbackup.h"

namespace uaw = unity::autopilot_wrapper;

class FDBackup :
    public ::testing::Test
{
    public:

        FDBackup ();

    protected:

        int                             pipe[2];
        std::unique_ptr <uaw::FDBackup> backup;
};

FDBackup::FDBackup ()
{
    if (pipe2 (pipe, O_CLOEXEC) == -1)
        throw std::runtime_error (strerror (errno));

    backup.reset (new uaw::FDBackup (pipe[0]));

    close (pipe[0]);
}

TEST_F (FDBackup, Restore)
{
    char msg[2] = "a";

    ssize_t amountWritten = write (pipe[1],
                                   static_cast <void *> (msg),
                                   1);

    if (amountWritten == -1)
        throw std::runtime_error (strerror (errno));

    backup.reset ();

    struct pollfd pfd;
    pfd.events = POLLIN | POLLOUT | POLLHUP;
    pfd.revents = 0;
    pfd.fd = pipe[0];

    int ready = poll (&pfd, 1, 0);

    if (ready == -1)
        throw std::runtime_error (strerror (errno));

    EXPECT_EQ (1, ready) << "Expected data available to be read on "
                            "restored fd";
}
