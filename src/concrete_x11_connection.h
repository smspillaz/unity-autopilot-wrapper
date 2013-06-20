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
            public X11Connection
        {
            public:

                class ConfigDeleter :
                    public XRRScreenConfigDeleter
                {
                    public:

                        typedef XRRScreenConfiguration SConf;

                        virtual ~ConfigDeleter ();
                        virtual void operator() (SConf *) const;
                };

                Display * OpenDisplay (char *arg) const;
                int CloseDisplay (Display *disp) const;
                XRRScreenConfiguration *
                GetConfig (Display *display) const;
                ScreenSizeArray
                GetScreenSizes (ScreenConfig const &) const;
                void ChangeSizeIndex (Display *,
                                      ScreenConfig const &,
                                      unsigned int index) const;
        };
    }
}
#endif
