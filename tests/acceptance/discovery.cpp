/*
 * discovery.cpp
 *
 * Test that autopilot output is parsed correctly and
 * tests are discovered
 *
 * See LICENSE.md for Copyright information.
 */

#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "listtests.h"
#include "tmpenv.h"

#include "uaw_acceptance_tests_config.h"

using ::testing::ElementsAreArray;

namespace uaw = unity::autopilot_wrapper;
namespace uawt = unity::autopilot_wrapper::test;

class Discovery :
    public ::testing::Test
{
    public:

        Discovery () :
            path ("PATH", (std::string (uawt::SimpleExecutableDirectory) +
                           ":" + getenv ("PATH")).c_str ()),
            params (uaw::AllAutopilotTestsIn ("fake"))
        {
        }

        uawt::TmpEnv                                    path;
        testing::internal::ParamGenerator <std::string> params;
};

TEST_F (Discovery, AllTests)
{
    std::string const ExpectedElements[] =
    {
        "fake.fake1",
        "fake.fake2",
        "fake.fake3",
        "fake.fake4",
        "fake.fake5",
        "fake.fake6"
    };

    /* Convert back to a vector */
    std::vector <std::string> elements;

    for (auto const &i : params)
        elements.push_back (i);

    EXPECT_THAT (elements, ElementsAreArray (ExpectedElements));
}

TEST_F (Discovery, OneTest)
{
    params = uaw::AllAutopilotTestsIn ("fake.fake1");

    std::string const ExpectedElements[] =
    {
        "fake.fake1",
    };

    /* Convert back to a vector */
    std::vector <std::string> elements;

    for (auto const &i : params)
        elements.push_back (i);

    EXPECT_THAT (elements, ElementsAreArray (ExpectedElements));
}
