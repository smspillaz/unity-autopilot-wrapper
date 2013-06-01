/*
 * redirectedfd.h
 *
 * Utility class to redirect operations on one
 * file descriptor into another until destruction.
 *
 * See LICENSE.md for Copyright information
 */
#ifndef UAW_REDIRECTEDFD_H
#define UAW_REDIRECTEDFD_H

namespace unity
{
    namespace autopilot_wrapper
    {
        class RedirectedFD
        {
            public:

                RedirectedFD (int from,
                              int &to);
                ~RedirectedFD ();


            private:

                RedirectedFD (RedirectedFD const &) = delete;
                RedirectedFD (RedirectedFD &&) = delete;
                RedirectedFD & operator= (RedirectedFD const &) = delete;

                int &mToFd;
        };
    }
}

#endif
