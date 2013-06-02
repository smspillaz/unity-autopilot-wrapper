/*
 * unity_autopilot_test.h
 *
 * A simple test fixture and test for wrapping
 * an autopilot test in a particular environment
 *
 * See LICENSE.md for Copyright information.
 */

#ifndef UAW_UNITY_AUTOPILOT_TEST_H
#define UAW_UNITY_AUTOPILOT_TEST_H

#include <iostream>

#include <gtest/gtest.h>

#include "pipe.h"
#include "launch.h"
#include "locatebinary.h"
#include "readfd.h"

namespace unity
{
    namespace autopilot_wrapper
    {
        class Autopilot :
            public ::testing::TestWithParam <std::string>
        {
            protected:

                void PrintStderr ()
                {
                    std::string output =
                        FdToString (AutopilotStderrPipe.ReadEnd ());

                    std::cout << "[== TEST ERRORS ==]" << std::endl
                              << output
                              << std::endl;
                }

                void PrintStdout ()
                {
                    std::string output =
                        FdToString (AutopilotStdoutPipe.ReadEnd ());

                    std::cout << "[== TEST MESSAGES ==]" << std::endl
                              << output
                              << std::endl;
                }

                Pipe AutopilotStderrPipe;
                Pipe AutopilotStdoutPipe;
        };

        TEST_P (Autopilot, Run)
        {
            char const *AutopilotOptions[] =
            {
                locateBinary ("autopilot").c_str (),
                "run",
                "-v",
                GetParam ().c_str (),
                NULL
            };

            int status =
                launchBinaryAndWaitForReturn (AutopilotOptions[0],
                                              AutopilotOptions,
                                              AutopilotStdoutPipe.WriteEnd (),
                                              AutopilotStderrPipe.WriteEnd ());

            /* Create a task to allow it to close eventually */
            EXPECT_EQ (status, 0) << "expected exit status of 0";

            if (status)
            {
                PrintStdout ();
                PrintStderr ();
            }
            else
            {
                /* Extra space here to align with gtest output */
                std::cout << "[AUTOPILOT ] Pass test " << GetParam () << std::endl;
            }
        }
    }
}

#endif
