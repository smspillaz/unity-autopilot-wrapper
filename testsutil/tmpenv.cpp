/*
 * tmpenv.cpp
 * 
 * Helper class to push / pop environment variables
 *
 * See LICENSE.md for Copyright information
 */

#include <stdlib.h>

#include "tmpenv.h"

namespace uawt = unity::autopilot_wrapper::test;

uawt::TmpEnv::TmpEnv (char const *key,
                      char const *value) :
    key (key)
{
    char *old = getenv (key);
    oldValue = old ? old : "";
    setenv (key, value, 1);
}

uawt::TmpEnv::~TmpEnv ()
{
    setenv (key, oldValue.c_str (), 1);
}
