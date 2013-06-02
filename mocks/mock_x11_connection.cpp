/*
 * mock_x11_connection.cpp
 *
 * Mocked out XOpenDisplay / XCloseDisplay functions
 *
 * See LICENSE.md for Copyright information
 */

#include <gmock/gmock.h>

#include "mock_x11_connection.h"

namespace uawm = unity::autopilot_wrapper::mocks;

uawm::MockX11Connection::MockX11Connection ()
{
}

uawm::MockX11Connection::~MockX11Connection ()
{
}
