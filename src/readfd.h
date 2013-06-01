/*
 * readfd.h
 *
 * Utility function to read a file descriptor for data
 * into a string
 *
 * See LICENSE.md for Copyright information
 */
#ifndef UAW_READFD_H
#define UAW_READFD_H

#include <string>

namespace unity
{
    namespace autopilot_wrapper
    {
        std::string FdToString (int fd);
    }
}

#endif
