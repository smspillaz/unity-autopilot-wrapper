/*
 * concrete_x11_connection.h
 *
 * An implementation of the X11 interface that connects to a real server
 *
 * See LICENSE.md for Copyright information
 */
#ifndef UAW_CONCRETE_X11_CONNECTION_H
#define UAW_CONCRETE_X11_CONNECTION_H

#include <x11_connection.h>

namespace unity
{
    namespace autopilot_wrapper
    {
        class ConcreteX11Connection :
            public unity::autopilot_wrapper::X11Connection
        {
            public:

                Display * OpenDisplay (char *arg) const;
                int CloseDisplay (Display *disp) const;
                ScreenSizeArray GetScreenSizes (Display *) const;
                void ChangeSizeIndex (Display *, unsigned int index) const;
        };
    }
}
#endif
