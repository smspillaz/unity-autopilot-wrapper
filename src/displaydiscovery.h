/*
 * displaydiscovery.h
 *
 * Keep opening server connections until one fails to determine
 * a safe display number to use
 *
 * See LICENSE.md for Copyright information.
 */

#ifndef UAW_DISPLAYDISCOVERY_H
#define UAW_DISPLAYDISCOVERY_H

namespace unity
{
    namespace autopilot_wrapper
    {
        class X11Connection;

        int FindAvailableDisplayNumber (X11Connection const &);
    }
}

#endif
