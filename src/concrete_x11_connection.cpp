/*
 * concrete_x11_connection.cpp
 *
 * An implementation of the X11 interface that connects to a real server
 *
 * See LICENSE.md for Copyright information
 */

#include <X11/Xlib.h>

#include "x11_connection.h"
#include "concrete_x11_connection.h"

namespace uaw = unity::autopilot_wrapper;

Display *
uaw::ConcreteX11Connection::OpenDisplay (char *arg) const
{
    return XOpenDisplay (arg);
}

int
uaw::ConcreteX11Connection::CloseDisplay (Display *disp) const
{
    return XCloseDisplay (disp);
}

uaw::ScreenSizeArray
uaw::ConcreteX11Connection::GetScreenSizes (Display *disp) const
{
    return uaw::ScreenSizeArray ();
}

void
uaw::ConcreteX11Connection::ChangeSizeIndex (Display      *disp,
                                             unsigned int index) const
{
}
