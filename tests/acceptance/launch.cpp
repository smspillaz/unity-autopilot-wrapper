/*
 * launch.cpp
 *
 * Test that when we launch a binary we can collect
 * its return code, output etc
 *
 * See LICENCE.md for Copyright information
 */

#include <gtest/gtest.h>

#include "launch.h"
#include "pipe.h"
#include "readfd.h"

#include "uaw_acceptance_tests_config.h"

namespace uaw = unity::autopilot_wrapper;
namespace uawt = unity::autopilot_wrapper::test;

class Launch :
    public ::testing::Test
{
    public:

        Launch ();

    protected:

        std::string const executable;
        uaw::Pipe         stderrPipe;
        uaw::Pipe         stdoutPipe;
};

Launch::Launch () :
    executable (std::string (uawt::SimpleExecutableDirectory) +
                std::string (uawt::SimpleExecutable))
{
}

TEST_F (Launch, CaptureStdout)
{
    char const *argv = NULL;
    uaw::launchBinaryAndWaitForReturn (executable,
                                       &argv,
                                       stderrPipe.WriteEnd (),
                                       stdoutPipe.WriteEnd ());

    std::string output = uaw::FdToString (stdoutPipe.ReadEnd ());
    EXPECT_EQ ("output\n", output);
}

TEST_F (Launch, CaptureStderr)
{
    char const *argv = NULL;
    uaw::launchBinaryAndWaitForReturn (executable,
                                       &argv,
                                       stderrPipe.WriteEnd (),
                                       stdoutPipe.WriteEnd ());

    std::string error = uaw::FdToString (stderrPipe.ReadEnd ());
    EXPECT_EQ ("error\n", error);
}

TEST_F (Launch, ReturnCode)
{
    char const *argv = NULL;
    int ret = uaw::launchBinaryAndWaitForReturn (executable,
                                                 &argv,
                                                 stderrPipe.WriteEnd (),
                                                 stdoutPipe.WriteEnd ());

    EXPECT_EQ (0, ret);
}
