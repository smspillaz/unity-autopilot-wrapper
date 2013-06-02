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

typedef struct _XDisplay Display;

namespace unity
{
    namespace autopilot_wrapper
    {
        class X11Connection
        {
            public:

                X11Connection ();
                virtual ~X11Connection ();

                virtual Display * OpenDisplay (char *) const = 0;
                virtual int CloseDisplay (Display *) const = 0;

            private:

                X11Connection (X11Connection const &) = delete;
                X11Connection (X11Connection &&) = delete;
                X11Connection & operator= (X11Connection const &) = delete;
        };
    }
}

#endif
