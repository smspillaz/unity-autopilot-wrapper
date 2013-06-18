/*
 * resizescreen.h
 *
 * Utility functions to change the screen size for testing purposes
 *
 * See LICENSE.md for Copyright information
 */
#ifndef UAW_RESIZESCREEN_H
#define UAW_RESIZESCREEN_H

typedef struct _XDisplay Display;

namespace unity
{
    namespace autopilot_wrapper
    {
        class X11Connection;

        static const unsigned int PreferredMinimumWidth = 1280;
        static const unsigned int PreferredMinimumHeight = 1024;

        bool ScaleToPreferredMinimum (Display             *display,
                                      X11Connection const &connection);
    }
}
#endif
