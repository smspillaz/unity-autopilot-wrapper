/*
 * locatebinary.cpp
 *
 * Test traversing PATH until a suitable
 * instance of a binary can be located
 *
 * See LICENSE.md for Copyright information
 */

#include <gtest/gtest.h>

#include "uaw_acceptance_tests_config.h"

#include "tmpenv.h"
#include "locatebinary.h"

namespace uaw = unity::autopilot_wrapper;
namespace uawt = unity::autopilot_wrapper::test;

class LocateBinary :
    public ::testing::Test
{
    public:

        LocateBinary ();

    private:

        uawt::TmpEnv path;
};

namespace
{
    std::string const NewPath ("/:" +
                               std::string (uawt::SimpleExecutableDirectory) +
                               ":" +
                               getenv ("PATH"));
    std::string const NoExecutable ("______none______");
}

LocateBinary::LocateBinary () :
    path ("PATH", NewPath.c_str ())
{
}

TEST_F (LocateBinary, SimpleExecutable)
{
    std::string const SimpleExecutableLocation =
        uaw::locateBinary (uawt::SimpleExecutable);

    EXPECT_EQ (std::string (uawt::SimpleExecutableDirectory) + "/" +
               uawt::SimpleExecutable,
               SimpleExecutableLocation);
}

TEST_F (LocateBinary, NoExecutable)
{
    std::string const NoExecutableLocation =
        uaw::locateBinary (NoExecutable);

    EXPECT_EQ ("",
               NoExecutableLocation);
}
