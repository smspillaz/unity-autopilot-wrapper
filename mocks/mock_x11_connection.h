/*
 * mock_x11_connection.h
 *
 * Mocked out XOpenDisplay / XCloseDisplay functions
 *
 * See LICENSE.md for Copyright information
 */
#ifndef UAW_MOCK_X11_CONNECTION_H
#define UAW_MOCK_X11_CONNECTION_H

#include <gmock/gmock.h>
#include "x11_connection.h"

namespace unity
{
    namespace autopilot_wrapper
    {
        namespace mocks
        {
            class MockX11Connection :
                public X11Connection
            {
                public:

                    typedef ScreenSizeArray        Sizes;
                    typedef XRRScreenConfiguration SConf;
                    typedef ScreenConfig           SCPtr;

                    MockX11Connection ();
                    ~MockX11Connection ();

                    MOCK_CONST_METHOD1 (OpenDisplay, Display * (char *));
                    MOCK_CONST_METHOD1 (CloseDisplay, int (Display *));
                    MOCK_CONST_METHOD1 (GetConfig, SConf * (Display *));
                    MOCK_CONST_METHOD1 (GetScreenSizes, Sizes (SCPtr const &));
                    MOCK_CONST_METHOD3 (ChangeSizeIndex, void (Display *,
                                                               SCPtr const &,
                                                               unsigned int));
            };
        }
    }
}

#endif
