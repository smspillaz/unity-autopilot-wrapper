/*
 * listtest.cpp
 *
 * Find all autopilot tests containing some
 * string
 *
 * See LICENSE.md for Copyright information.
 */

#include <gtest/gtest.h>

#include <string>
#include <vector>

#include <boost/algorithm/string.hpp>

#include "launch.h"
#include "listtests.h"
#include "locatebinary.h"
#include "pipe.h"
#include "readfd.h"

namespace uaw = unity::autopilot_wrapper;

namespace
{
    std::vector <std::string> AllAutopilotTests ()
    {
        uaw::Pipe stderr;
        uaw::Pipe stdout;

        char const *AutopilotListOptions[] =
        {
            uaw::locateBinary ("autopilot").c_str (),
            "list",
            "unity",
            NULL
        };

        int status =
            uaw::launchBinaryAndWaitForReturn (AutopilotListOptions[0],
                                               AutopilotListOptions,
                                               stderr.WriteEnd (),
                                               stdout.WriteEnd ());

        if (status != 0)
            throw std::runtime_error ("autopilot list unity failed");

        std::string autopilotOutput = uaw::FdToString (stdout.ReadEnd ());
        std::vector <std::string> lines;

        boost::split (lines, autopilotOutput, boost::is_any_of ("\n"));

        /* Remove the first three lines */
        lines.erase (lines.begin (),
                     lines.begin () + 2);

        /* Remove last three lines */
        lines.pop_back ();
        lines.pop_back ();
        lines.pop_back ();

        std::vector <std::string> values;
        for (std::string const & line : lines)
        {
            if (!line.empty ())
                values.push_back (line.substr (4));
        }

        return values;
    }
}

testing::internal::ParamGenerator <std::string>
uaw::AllAutopilotTestsIn (std::string const &module)
{
    static std::vector <std::string> allTests = AllAutopilotTests ();

    std::vector <std::string> requestedTests;
    for (std::string const & test : allTests)
    {
        if (test.find (module) != std::string::npos)
            requestedTests.push_back (test);
    }

    return ::testing::ValuesIn (requestedTests);
}
