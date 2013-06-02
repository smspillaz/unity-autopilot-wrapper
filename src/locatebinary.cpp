/*
 * locatebinary.cpp
 *
 * Traverse PATH until a suitable instance
 * of a binary can be located
 *
 * See LICENSE.md for Copyright information
 */

#include <stdexcept>

#include <boost/tokenizer.hpp>

#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

#include "locatebinary.h"

namespace uaw = unity::autopilot_wrapper;

std::string uaw::locateBinary (std::string const &binaryName)
{
    std::string pathString (getenv ("PATH"));
    boost::char_separator <char> sep (":");
    boost::tokenizer <boost::char_separator <char> > paths (pathString, sep);

    for (std::string const &path : paths)
    {
        std::string binary (path + "/" + binaryName);
        int ok = access (binary.c_str (), X_OK);

        if (ok == -1)
        {
            switch (errno)
            {
                case EACCES:
                case ENOENT:
                    continue;
                default:
                    throw std::runtime_error (strerror (errno));
            }
        }

        return binary;
    }

    return "";
}
