/*
 * exports.h
 *
 * Utility functions to export some environment variables
 * based on program input
 *
 * See LICENSE.md for Copyright information.
 */

#ifndef UAW_EXPORTS_H
#define UAW_EXPORTS_H

#include <string>

namespace unity
{
    namespace autopilot_wrapper
    {
        void ExportDisplay (int);
        bool FindDbusEnvironmentVars (std::string const &);
        void ExportDbusEnvironmentVars (std::string const &);
        void ExportUnityEnvironmentVars (std::string const &,
                                         std::string const &,
                                         std::string const &);
    }
}

#endif
