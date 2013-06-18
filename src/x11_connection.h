/*
 * x11_connection.h
 *
 * Provide a simple interface to connect to
 * an X Server
 *
 * See LICENSE.md for Copyright information
 */
#ifndef UAW_X11_CONNECTION_H
#define UAW_X11_CONNECTION_H

#include <boost/shared_array.hpp>

#include <X11/extensions/Xrandr.h>

typedef struct _XDisplay Display;

namespace unity
{
    namespace autopilot_wrapper
    {
        struct ScreenSizeArray
        {
            typedef boost::shared_array <XRRScreenSize> Array;

            Array        array;
            unsigned int num;
        };

        class X11Connection
        {
            public:

                X11Connection ();
                virtual ~X11Connection ();

                virtual Display * OpenDisplay (char *) const = 0;
                virtual int CloseDisplay (Display *) const = 0;
                virtual ScreenSizeArray GetScreenSizes (Display *) const = 0;
                virtual void ChangeSizeIndex (Display *, unsigned int index) const = 0;

            private:

                X11Connection (X11Connection const &) = delete;
                X11Connection (X11Connection &&) = delete;
                X11Connection & operator= (X11Connection const &) = delete;
        };
    }
}

#endif
