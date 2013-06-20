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

#include <memory>

#include <X11/extensions/Xrandr.h>

typedef struct _XDisplay Display;

namespace unity
{
    namespace autopilot_wrapper
    {
        struct ScreenSizeArray
        {
            XRRScreenSize *array;
            int           num;
        };

        class XRRScreenConfigDeleter
        {
            public:

                virtual ~XRRScreenConfigDeleter ();
                virtual void operator() (XRRScreenConfiguration *) const;
        };

        typedef std::unique_ptr <XRRScreenConfiguration,
                                 const XRRScreenConfigDeleter &> ScreenConfig;

        class X11Connection
        {
            public:

                X11Connection ();
                virtual ~X11Connection ();

                virtual Display * OpenDisplay (char *) const = 0;
                virtual int CloseDisplay (Display *) const = 0;

                /* This is a little bit awkward as we're unable to return
                 * unique_ptrs from Google Mock because they are not
                 * copyable. Clients should store the return value
                 * in a unique_ptr */
                virtual XRRScreenConfiguration *
                GetConfig (Display *display) const = 0;
                virtual ScreenSizeArray
                GetScreenSizes (ScreenConfig const &) const = 0;
                virtual void ChangeSizeIndex (Display *,
                                              ScreenConfig const &,
                                              unsigned int index) const = 0;

            private:

                X11Connection (X11Connection const &) = delete;
                X11Connection (X11Connection &&) = delete;
                X11Connection & operator= (X11Connection const &) = delete;
        };
    }
}

#endif
