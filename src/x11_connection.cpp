/*
 * x11_connection.cpp
 *
 * Provide a simple interface to connect to
 * an X Server
 *
 * See LICENSE.md for Copyright information
 */

#include "x11_connection.h"

namespace uaw = unity::autopilot_wrapper;

uaw::XRRScreenConfigDeleter::~XRRScreenConfigDeleter ()
{
}

void
uaw::XRRScreenConfigDeleter::operator() (XRRScreenConfiguration *) const
{
}

uaw::X11Connection::X11Connection ()
{
}

uaw::X11Connection::~X11Connection ()
{
}
