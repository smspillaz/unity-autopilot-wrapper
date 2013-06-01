/*
 * pipe.h
 *
 * Utility class to create a unix pipe and
 * close it on teardown
 *
 * See LICENSE.md for Copyright information
 */
#ifndef UAW_PIPE_H
#define UAW_PIPE_H

namespace unity
{
    namespace autopilot_wrapper
    {
        class Pipe
        {
            public:

                Pipe ();
                ~Pipe ();

                /* Read end descriptor is read-only */
                int ReadEnd ();

                /* Write end descriptor is writable, we need to close it
                 * from other objects */
                int & WriteEnd ();

            private:

                Pipe (Pipe const &) = delete;
                Pipe (Pipe &&) = delete;
                Pipe & operator= (Pipe const &) = delete;

                int mPipe[2];
        };
    }
}

#endif
