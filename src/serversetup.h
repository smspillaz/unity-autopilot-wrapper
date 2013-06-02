/*
 * serversetup.h
 *
 * Determine which XServer is meant to be running
 * and configure the XServer object appropriately
 *
 * See LICENSE.md for Copyright information.
 */
#ifndef UAW_SERVERSETUP_H
#define UAW_SERVERSETUP_H

#include "servertype.h"

namespace xorg
{
    namespace testing
    {
        class XServer;
    }
}

namespace unity
{
    namespace autopilot_wrapper
    {
        void SetupServer (xorg::testing::XServer &,
                          int);
        void CustomizeServer (xorg::testing::XServer &,
                              ServerType);
    }
}
#endif
