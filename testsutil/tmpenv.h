/*
 * tmpenv.h
 * 
 * Helper class to push / pop environment variables
 *
 * See LICENSE.md for Copyright information
 */
#ifndef UAW_TMPENV_H
#define UAW_TMPENV_H

#include <string>

namespace unity
{
    namespace autopilot_wrapper
    {
        namespace test
        {
            class TmpEnv
            {
                public:

                    TmpEnv (char const *, char const *);
                    ~TmpEnv ();

                private:

                    TmpEnv (TmpEnv const &) = delete;
                    TmpEnv (TmpEnv &&) = delete;
                    TmpEnv & operator= (TmpEnv const &) = delete;

                    char const  *key;
                    std::string oldValue;
            };
        }
    }
}

#endif

