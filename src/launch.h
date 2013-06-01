/*
 * launch.h
 *
 * Utility function to launch a binary and collect
 * the return code, stdin and stdout
 *
 * See LICENSE.md for Copyright information
 */
#ifndef UAW_LAUNCH_H
#define UAW_LAUNCH_H

#include <string>
#include <unistd.h>

namespace unity
{
    namespace autopilot_wrapper
    {
        pid_t launchBinary (const std::string &executable,
                            const char        **argv,
                            int               &stderrWriteEnd,
                            int               &stdoutWriteEnd);
        int launchBinaryAndWaitForReturn (const std::string &executable,
                                          const char        **argv,
                                          int               &stderrWriteEnd,
                                          int               &stdoutWriteEnd);
    }
}


#endif
