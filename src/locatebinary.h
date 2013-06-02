/*
 * locatebinary.h
 *
 * Traverse PATH until a suitable instance
 * of a binary can be located
 *
 * See LICENSE.md for Copyright information
 */

#ifndef UAW_LOCATE_BINARY_H
#define UAW_LOCATE_BINARY_H

#include <string>

namespace unity
{
    namespace autopilot_wrapper
    {
        std::string locateBinary (std::string const &binaryName);
    }
}

#endif
