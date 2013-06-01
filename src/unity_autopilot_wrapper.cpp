/*
 * unity_autopilot_wrapper.cpp
 *
 * Wrapper to run autopilot tests specified
 *
 * See LICENSE.md for Copyright information
 */

#include <stdexcept>
#include <boost/noncopyable.hpp>
#include <gtest/gtest.h>

#include "pipe.h"
#include "launch.h"
#include "readfd.h"

#include "compiz_autopilot_tests.h"

using ::testing::ValuesIn;
using ::testing::WithParamInterface;

namespace uaw = unity::autopilot_wrapper;

namespace
{
    const char *autopilot = "/usr/bin/autopilot";
    const char *runOpt = "run";
    const char *dashV = "-v";
}

class CompizAutopilotAcceptanceTest :
    public ::testing::Test,
    public ::testing::WithParamInterface <char const *>
{
    public:

        CompizAutopilotAcceptanceTest ();
        const char ** GetAutopilotArgv ();
        void PrintChildStderr ();
        void PrintChildStdout ();

    protected:

        std::vector <const char *> autopilotArgv;
        uaw::Pipe                  childStdoutPipe;
        uaw::Pipe                  childStderrPipe;
};

CompizAutopilotAcceptanceTest::CompizAutopilotAcceptanceTest ()
{
    autopilotArgv.push_back (autopilot);
    autopilotArgv.push_back (runOpt);
    autopilotArgv.push_back (dashV);
    autopilotArgv.push_back (GetParam ());
    autopilotArgv.push_back (NULL);
}

const char **
CompizAutopilotAcceptanceTest::GetAutopilotArgv ()
{
    return &autopilotArgv[0];
}

void
CompizAutopilotAcceptanceTest::PrintChildStderr ()
{
    std::string output = uaw::FdToString (childStderrPipe.ReadEnd ());

    std::cout << "[== TEST ERRORS ==]" << std::endl
              << output
              << std::endl;
}

void
CompizAutopilotAcceptanceTest::PrintChildStdout ()
{
    std::string output = uaw::FdToString (childStdoutPipe.ReadEnd ());

    std::cout << "[== TEST MESSAGES ==]" << std::endl
              << output
              << std::endl;
}

TEST_P (CompizAutopilotAcceptanceTest, AutopilotTest)
{
    std::string scopedTraceMsg ("Running Autopilot Test");
    scopedTraceMsg += GetParam ();

    int status =
        uaw::launchBinaryAndWaitForReturn (std::string (autopilot),
                                           GetAutopilotArgv (),
                                           childStderrPipe.WriteEnd (),
                                           childStdoutPipe.WriteEnd ());

    EXPECT_EQ (status, 0) << "expected exit status of 0";

    if (status)
    {
        PrintChildStdout ();
        PrintChildStderr ();
    }
    else
    {
        /* Extra space here to align with gtest output */
        std::cout << "[AUTOPILOT ] Pass test " << GetParam () << std::endl;
    }
}

INSTANTIATE_TEST_CASE_P (UnityIntegrationAutopilotTests, CompizAutopilotAcceptanceTest,
                         ValuesIn (AutopilotTests));
