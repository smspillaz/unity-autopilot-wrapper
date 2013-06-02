/*
 * displaydiscovery.cpp
 *
 * Test display discovery mechanism using
 * a mocked out X Connection
 *
 * See LICENSE.md for Copyright information.
 */

#include <stdexcept>

#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <boost/lexical_cast.hpp>

#include "displaydiscovery.h"
#include "x11_connection.h"

#include "mock_x11_connection.h"
#include "is_display_number_matcher.h"

using ::testing::_;
using ::testing::AtLeast;
using ::testing::Matcher;
using ::testing::MatcherInterface;
using ::testing::MakeMatcher;
using ::testing::MatchResultListener;
using ::testing::Return;
using ::testing::ReturnNull;
using ::unity::autopilot_wrapper::matchers::IsDisplayNumber;

namespace uaw = unity::autopilot_wrapper;
namespace uawm = unity::autopilot_wrapper::mocks;

struct _XDisplay
{
};

class DisplayDiscovery :
    public ::testing::Test
{
    public:

        void IgnoreConnections ()
        {
            EXPECT_CALL (connection, OpenDisplay (_)).Times (AtLeast (0));
            EXPECT_CALL (connection, CloseDisplay (_)).Times (AtLeast (0));
        }

        void AlwaysBusy ()
        {
            ON_CALL (connection, OpenDisplay (_)).WillByDefault (Return (&fakeDisplay));
        }

        testing::internal::TypedExpectation <Display * (char *)> &
        ExpectConnectionOnDisplayNum (int num)
        {
            return EXPECT_CALL (connection, OpenDisplay (IsDisplayNumber (num)))
                       .Times (AtLeast (0));
        }

    protected:

        Display                 fakeDisplay;
        uawm::MockX11Connection connection;
};

TEST_F (DisplayDiscovery, MaxOutThrows)
{
    IgnoreConnections ();
    AlwaysBusy ();

    EXPECT_THROW ({
        uaw::FindAvailableDisplayNumber (connection);
    }, std::runtime_error);
}

TEST_F (DisplayDiscovery, FindSecond)
{
    IgnoreConnections ();
    AlwaysBusy ();
    ExpectConnectionOnDisplayNum (1).WillOnce (ReturnNull ());

    EXPECT_EQ (1, uaw::FindAvailableDisplayNumber (connection));
}
