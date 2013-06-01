/*
 * redirectedfd.cpp
 *
 * Test redirecting one fd to another
 *
 * See LICENSE.md for Copyright information
 */
#include <stdexcept>

#include <memory>

#include <gtest/gtest.h>

#include <stdio.h>
#include <sys/poll.h>
#include "fdbackup.h"
#include "pipe.h"
#include "redirectedfd.h"

namespace uaw = unity::autopilot_wrapper;

class RedirectedFD :
    public ::testing::Test
{
    public:

        RedirectedFD ();

    protected:

        uaw::Pipe from;
        uaw::Pipe to;
        std::unique_ptr <uaw::FDBackup> backup;
        std::unique_ptr <uaw::RedirectedFD> redirected;
};

namespace
{
    bool ReadyForReading (uaw::Pipe const &pipe)
    {
        /* There should be nothing to poll */
        struct pollfd pfd;
        pfd.events = POLLIN | POLLOUT | POLLHUP;
        pfd.revents = 0;
        pfd.fd = pipe.ReadEnd ();

        int n = poll (&pfd, 1, 0);

        if (n == -1)
            throw std::runtime_error (strerror (errno));

        return n > 0;
    }
}

RedirectedFD::RedirectedFD () :
    backup (new uaw::FDBackup (from.WriteEnd ()))
{
    if (close (from.WriteEnd ()) == -1)
        throw std::runtime_error (strerror (errno));

    redirected.reset (new uaw::RedirectedFD (from.WriteEnd (),
                                             to.WriteEnd ()));
}

TEST_F (RedirectedFD, NoWriteToOldFd)
{
    char buf[] = "a\0";
    ssize_t len = write (from.WriteEnd (), static_cast <void *> (buf), 1);

    if (len == -1)
        throw std::runtime_error (strerror (errno));

    /* There should be nothing to poll */
    EXPECT_FALSE (ReadyForReading (from)) << "Expected no data on from pipe";
}

TEST_F (RedirectedFD, WriteToNewFd)
{
    char buf[] = "a\0";
    ssize_t len = write (from.WriteEnd (), static_cast <void *> (buf), 1);

    if (len == -1)
        throw std::runtime_error (strerror (errno));

    /* There should be something to poll */
    EXPECT_TRUE (ReadyForReading (to)) << "Expected no data on to pipe";
}

TEST_F (RedirectedFD, RestoredWriteToOldFd)
{
    redirected.reset ();
    backup.reset ();

    char buf[] = "a\0";
    ssize_t len = write (from.WriteEnd (), static_cast <void *> (buf), 1);

    if (len == -1)
        throw std::runtime_error (strerror (errno));

    /* There should be nothing to poll */
    EXPECT_TRUE (ReadyForReading (from)) << "Expected data on from pipe";
}
