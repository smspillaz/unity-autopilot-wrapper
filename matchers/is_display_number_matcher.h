/*
 * is_display_number_matcher.cpp
 *
 * Determines if a display string is a display number
 *
 * See LICENSE.md for Copyright information
 */
#ifndef UAW_IS_DISPLAY_NUMBER_MATCHER_H
#define UAW_IS_DISPLAY_NUMBER_MATCHER_H

#include <gtest/gtest.h>
#include <gmock/gmock.h>

namespace unity
{
    namespace autopilot_wrapper
    {
        namespace matchers
        {
            class DisplayNumberMatcher :
                public ::testing::MatcherInterface <char *>
            {
                public:

                    typedef ::testing::MatchResultListener MRL;

                    DisplayNumberMatcher (int number);
                    bool MatchAndExplain (char *chars,
                                          MRL  *listener) const;
                    void DescribeTo (std::ostream *os) const;

                private:

                    int number;
            };

            inline testing::Matcher <char *> IsDisplayNumber (int number)
            {
                return testing::MakeMatcher (
                            new DisplayNumberMatcher (number));
            }
        }
    }
}
#endif
