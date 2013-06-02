/*
 * is_display_number_matcher.cpp
 *
 * Determines if a display string is a display number
 *
 * See LICENSE.md for Copyright information
 */

#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <boost/lexical_cast.hpp>

#include "is_display_number_matcher.h"

namespace uawmatch = unity::autopilot_wrapper::matchers;

using ::testing::MakeMatcher;
using ::testing::MatchResultListener;

uawmatch::DisplayNumberMatcher::DisplayNumberMatcher (int number) :
    number (number)
{
}

typedef testing::MatchResultListener MRL;

bool uawmatch::DisplayNumberMatcher::MatchAndExplain (char *chars,
                                                      MRL  *listener) const
{
    return number == boost::lexical_cast <int> (&chars[1]);
}

void uawmatch::DisplayNumberMatcher::DescribeTo (std::ostream *os) const
{
    *os << "contains number " << number << std::endl;
}
