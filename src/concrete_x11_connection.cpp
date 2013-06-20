/*
 * concrete_x11_connection.cpp
 *
 * An implementation of the X11 interface that connects to a real server
 *
 * See LICENSE.md for Copyright information
 */

#include <boost/bind.hpp>

#include <X11/Xlib.h>

#include "x11_connection.h"
#include "concrete_x11_connection.h"

namespace uaw = unity::autopilot_wrapper;

typedef XRRScreenConfiguration SConf;

uaw::ConcreteX11Connection::ConfigDeleter::~ConfigDeleter ()
{
}

void
uaw::ConcreteX11Connection::ConfigDeleter::operator() (SConf *c) const
{
    XRRFreeScreenConfigInfo (c);
}

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

XRRScreenConfiguration *
uaw::ConcreteX11Connection::GetConfig (Display *display) const
{
    return XRRGetScreenInfo (display, DefaultRootWindow (display));
}

uaw::ScreenSizeArray
uaw::ConcreteX11Connection::GetScreenSizes (ScreenConfig const &c) const
{
    uaw::ScreenSizeArray array;

    array.array = XRRConfigSizes (c.get (),
                                  &array.num);
    return array;
}

void
uaw::ConcreteX11Connection::ChangeSizeIndex (Display            *disp,
                                             ScreenConfig const &config,
                                             unsigned int       index) const
{
    XRRSetScreenConfig (disp,
                        config.get (),
                        DefaultRootWindow (disp),
                        index,
                        RR_Rotate_0,
                        CurrentTime);
}
