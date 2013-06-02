/*
 * exports.cpp
 *
 * Utility functions to export some environment variables
 * based on program input
 *
 * See LICENSE.md for Copyright information.
 */

#include <sstream>
#include <string>
#include <vector>

#include <boost/algorithm/string.hpp>

#include <cstdlib>

#include "exports.h"

namespace uaw = unity::autopilot_wrapper;

void uaw::ExportDisplay (int displayNumber)
{
    std::stringstream displayString;
    displayString << ":" << displayNumber;
    setenv ("DISPLAY", displayString.str ().c_str (), 1);
}

bool uaw::FindDbusEnvironmentVars (std::string const &DbusLaunchOutput)
{
    size_t DbusLaunchSessionBusAddress =
        DbusLaunchOutput.find ("DBUS_SESSION_BUS_ADDRESS");
    size_t DbusLaunchSessionBusPID =
        DbusLaunchOutput.find ("DBUS_SESSION_BUS_PID");
    size_t DbusLaunchSessionBusWindow =
        DbusLaunchOutput.find ("DBUS_SESSION_BUS_WINDOW");

    return DbusLaunchSessionBusAddress != std::string::npos &&
           DbusLaunchSessionBusPID != std::string::npos &&
           DbusLaunchSessionBusWindow != std::string::npos;
}

void uaw::ExportDbusEnvironmentVars (std::string const &DbusLaunchOutput)
{
    /* Split the string up into key/value pairs */
    std::vector <std::string> lines;

    boost::split (lines, DbusLaunchOutput, boost::is_any_of ("\n"));

    for (std::string const &line : lines)
    {
        if (line.empty ())
            continue;

        size_t firstEquals = line.find ("=");

        if (firstEquals == std::string::npos)
            continue;

        std::string value = line.substr (firstEquals + 1);
        std::string key = line.substr (0, firstEquals);

        /* Export the value */
        setenv (key.c_str (), value.c_str (), 1);
    }
}

void uaw::ExportUnityEnvironmentVars (std::string const &XDGConfigHome,
                                      std::string const &CompizConfigProfile,
                                      std::string const &CompizPluginPath)
{
    /* Export XDG_CONFIG_HOME */
    if (!XDGConfigHome.empty ())
        setenv ("XDG_CONFIG_HOME",
                XDGConfigHome.c_str (), 1);

    /* Export COMPIZ_CONFIG_PROFILE */
    if (!CompizConfigProfile.empty ())
        setenv ("COMPIZ_CONFIG_PROFILE",
                CompizConfigProfile.c_str (), 1);

    /* Export COMPIZ_PLUGIN_PATH */
    if (!CompizPluginPath.empty ())
        setenv ("COMPIZ_PLUGIN_DIR",
                CompizPluginPath.c_str (), 1);

    /* Export UNITY_LOG_SEVERITY */
    setenv ("UNITY_LOG_SEVERITY", "<root>=INFO", 1);
}
