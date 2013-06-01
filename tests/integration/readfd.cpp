/*
 * readfd.cpp
 *
 * Test reading from an arbitrary fd.
 *
 * See LICENSE.md for Copyright information
 */

#include <stdexcept>

#include <gtest/gtest.h>

#include <unistd.h>
#include <errno.h>

#include "pipe.h"
#include "readfd.h"

namespace uaw = unity::autopilot_wrapper;

class ReadFD :
    public ::testing::Test
{
    protected:

        uaw::Pipe pipe;
};

TEST_F (ReadFD, ReadFromPipe)
{
    std::string const msg ("mock_data");
    void const *cdata = static_cast <void const *> (msg.c_str ());
    void *data = const_cast <void *> (cdata);

    ssize_t amountWritten = write (pipe.WriteEnd (),
                                   data,
                                   msg.size ());

    if (amountWritten == -1)
        throw std::runtime_error (strerror (errno));

    std::string msgReceived = uaw::FdToString (pipe.ReadEnd ());

    EXPECT_EQ (msg, msgReceived);
}

TEST_F (ReadFD, ReadNone)
{
    std::string msgReceived = uaw::FdToString (pipe.ReadEnd ());

    EXPECT_EQ ("", msgReceived);
}
