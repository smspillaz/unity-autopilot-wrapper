/*
 * listtest.cpp
 *
 * Find all autopilot tests containing some
 * string
 *
 * See LICENSE.md for Copyright information.
 */

#ifndef UAW_LISTTESTS_H
#define UAW_LISTTESTS_H

#include <string>
#include <gtest/gtest.h>

namespace unity
{
    namespace autopilot_wrapper
    {
        testing::internal::ParamGenerator <std::string>
        AllAutopilotTestsIn (std::string const &module);
    }
}

#endif
