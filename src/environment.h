/*
 * environment.cpp
 *
 * Subclass xorg::testing::Environment and set up
 * servers, compiz, etc
 *
 * See LICENSE.md for Copyright information.
 */

#ifndef UAW_ENVIRONMENT_H
#define UAW_ENVIRONMENT_H

#include <memory>

#include <gtest/gtest.h>

#include "servertype.h"

namespace unity
{
    namespace autopilot_wrapper
    {
        class X11Connection;

        class Environment :
            public ::testing::Environment
        {
            public:

                Environment (X11Connection const &);
                virtual ~Environment () {};

                void SetServerType (ServerType type);

                void SetDbusLaunchPath (std::string const &);
                void SetDbusLaunchOptions (char const **);

                void SetCompizPath (std::string const &);
                void SetCompizOptions (char const **);
                void SetCompizPluginPath (std::string const &);
                void SetCompizConfigProfile (std::string const &);
                void SetCompizConfigProfileConfigDir (std::string const &);

            private:

                virtual void SetUp ();
                virtual void TearDown ();

                Environment (Environment const &) = delete;
                Environment (Environment &&) = delete;
                Environment & operator= (Environment const &) = delete;

                class Private;
                std::shared_ptr <Private> priv;
        };
    }
}

#endif
