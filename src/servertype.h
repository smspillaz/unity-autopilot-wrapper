/*
 * servertype.h
 *
 * A short enum containing all the available
 * types of servers to launch on
 *
 * See LICENSE.md for Copyright information
 */
#ifndef UAW_SERVERTYPE_H
#define UAW_SERVERTYPE_H

namespace unity
{
    namespace autopilot_wrapper
    {
        enum class ServerType
        {
            Running,
            Headless,
            Xephyr
        };
    }
}

#endif
