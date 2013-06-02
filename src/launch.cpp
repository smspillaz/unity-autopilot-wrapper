/*
 * launch.cpp
 *
 * Utility function to launch a binary and collect
 * the return code, stdin and stdout
 *
 * See LICENSE.md for Copyright information
 */

#include <iostream>
#include <sstream>
#include <stdexcept>

#include <unistd.h>
#include <errno.h>
#include <sys/poll.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <string.h>

#include "fdbackup.h"
#include "redirectedfd.h"
#include "launch.h"

namespace uaw = unity::autopilot_wrapper;

pid_t uaw::launchBinary (const std::string &executable,
                         const char        **argv,
                         int               &stderrWriteEnd,
                         int               &stdoutWriteEnd)
{
    FDBackup stderr (STDERR_FILENO);
    FDBackup stdout (STDOUT_FILENO);

    /* Close the originals once they have been backed up
     * We have to do this here and not in the FDBackup
     * constructors because of an order-of-operations issue -
     * namely if we close an original file descriptor name
     * before duplicating another one, then there's a possibility
     * that the duplicated other one will get the same name as
     * the one we just closed, making us unable to restore
     * the closed one properly */
    if (close (STDERR_FILENO) == -1)
        throw std::runtime_error (strerror (errno));

    if (close (STDOUT_FILENO) == -1)
        throw std::runtime_error (strerror (errno));

    /* Replace the current process stderr and stdout with the write end
     * of the pipes. Now when someone tries to write to stderr or stdout
     * they'll write to our pipes instead */
    RedirectedFD pipedStderr (STDERR_FILENO, stderrWriteEnd);
    RedirectedFD pipedStdout (STDOUT_FILENO, stdoutWriteEnd);

    /* Fork process, child gets a copy of the pipe write ends
     * - the original pipe write ends will be closed on exec
     * but the duplicated write ends now taking the place of
     * stderr and stdout will not be */
    pid_t child = fork ();

    /* Child process */
    if (child == 0)
    {
        if (execvpe (executable.c_str (),
                     const_cast <char * const *> (argv),
                     environ) == -1)
        {
            std::cerr << "execvpe failed with error "
                      << errno
                      << std::endl
                      << " - binary "
                      << executable
                      << std::endl;
            abort ();
        }
    }
    /* Parent process - error */
    else if (child == -1)
        throw std::runtime_error (strerror (errno));

    /* The old file descriptors for the stderr and stdout
     * are put back in place, and pipe write ends closed
     * as the child is using them at return */

    return child;
}

int uaw::waitForProcessEnd (pid_t child)
{
    int status = 0;

    do
    {
        /* Wait around for the child to get a signal */
        pid_t waitChild = waitpid (child, &status, 0);
        if (waitChild == child)
        {
            /* If it died unexpectedly, say so */
            if (WIFSIGNALED (status))
            {
                std::stringstream ss;
                ss << "child killed by signal "
                   << WTERMSIG (status);
                throw std::runtime_error (ss.str ());
            }
        }
        else
        {
            /* waitpid () failed */
            throw std::runtime_error (strerror (errno));
        }

        /* Keep going until it exited */
    } while (!WIFEXITED (status) && !WIFSIGNALED (status));

    /* Return the exit code */
    return WEXITSTATUS (status);
}

int uaw::launchBinaryAndWaitForReturn (const std::string &executable,
                                       const char        **argv,
                                       int               &stderrWriteEnd,
                                       int               &stdoutWriteEnd)
{
    pid_t child = launchBinary (executable,
                                argv,
                                stderrWriteEnd,
                                stdoutWriteEnd);

    return waitForProcessEnd (child);
}
