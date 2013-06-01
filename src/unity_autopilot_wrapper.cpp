/*
 * unity_autopilot_wrapper.cpp
 *
 * Wrapper to run autopilot tests specified
 *
 * See LICENSE.md for Copyright information
 */

#include <stdexcept>
#include <boost/noncopyable.hpp>

#include "nonportable_gnu.h"

#include <unistd.h>
#include <sys/poll.h>
#include <fcntl.h>
#include <errno.h>

#include <gtest/gtest.h>

#include "compiz_autopilot_tests.h"

using ::testing::ValuesIn;
using ::testing::WithParamInterface;

namespace
{
    class Pipe :
        boost::noncopyable
    {
        public:

            Pipe ()
            {
                if (pipe2 (mPipe, O_CLOEXEC) == -1)
                    throw std::runtime_error (strerror (errno));
            }

            ~Pipe ()
            {
                if (mPipe[0] &&
                    close (mPipe[0]) == -1)
                    std::cerr << "mPipe[0] " << strerror (errno) << std::endl;

                if (mPipe[1] &&
                    close (mPipe[1]) == -1)
                    std::cerr << "mPipe[0] " << strerror (errno) << std::endl;
            }

            /* Read end descriptor is read-only */
            int ReadEnd ()
            {
                return mPipe[0];
            }

            /* Write end descriptor is writable, we need to close it
             * from other objects */
            int & WriteEnd ()
            {
                return mPipe[1];
            }

        private:

            int mPipe[2];
    };

    class FileDescriptorBackup :
        boost::noncopyable
    {
        public:

            FileDescriptorBackup (int fd) :
                mOriginalFd (fd),
                mBackupFd (0)
            {
                mBackupFd = dup (mOriginalFd);

                /* Save original */
                if (mBackupFd == -1)
                    throw std::runtime_error (strerror (errno));
            }

            ~FileDescriptorBackup ()
            {
                /* Redirect backed up fd to old fd location */
                if (mBackupFd &&
                    dup2 (mBackupFd, mOriginalFd) == -1)
                    std::cerr << "Failed to restore file descriptor "
                              << strerror (errno) << std::endl;
            }

        private:

            int mOriginalFd;
            int mBackupFd;
    };

    class RedirectedFileDescriptor :
        boost::noncopyable
    {
        public:

            RedirectedFileDescriptor (int from,
                                      int &to) :
                mFromFd (from),
                mToFd (to)
            {
                /* Make 'to' take the old file descriptor's place */
                if (dup2 (to, from) == -1)
                    throw std::runtime_error (strerror (errno));
            }

            ~RedirectedFileDescriptor ()
            {
                if (mToFd &&
                    close (mToFd) == -1)
                    std::cerr << "Failed to close redirect-to file descriptor "
                              << strerror (errno) << std::endl;

                mToFd = 0;
            }

        private:

            int mFromFd;
            int &mToFd;
    };

    pid_t launchBinary (const std::string &executable,
                        const char        **argv,
                        int               &stderrWriteEnd,
                        int               &stdoutWriteEnd)
    {
        FileDescriptorBackup stderr (STDERR_FILENO);
        FileDescriptorBackup stdout (STDOUT_FILENO);

        /* Close the originals once they have been backed up
         * We have to do this here and not in the FileDescriptorBackup
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
        RedirectedFileDescriptor pipedStderr (STDERR_FILENO, stderrWriteEnd);
        RedirectedFileDescriptor pipedStdout (STDOUT_FILENO, stdoutWriteEnd);

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

    int launchBinaryAndWaitForReturn (const std::string &executable,
                                      const char        **argv,
                                      int               &stderrWriteEnd,
                                      int               &stdoutWriteEnd)
    {
        int status = 0;
        pid_t child = launchBinary (executable,
                                    argv,
                                    stderrWriteEnd,
                                    stdoutWriteEnd);

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

    const char *autopilot = "/usr/bin/autopilot";
    const char *runOpt = "run";
    const char *dashV = "-v";
}

class CompizAutopilotAcceptanceTest :
    public ::testing::Test,
    public ::testing::WithParamInterface <char const *>
{
    public:

        CompizAutopilotAcceptanceTest ();
        const char ** GetAutopilotArgv ();
        void PrintChildStderr ();
        void PrintChildStdout ();

    protected:

        std::vector <const char *> autopilotArgv;
        Pipe                       childStdoutPipe;
        Pipe                       childStderrPipe;
};

CompizAutopilotAcceptanceTest::CompizAutopilotAcceptanceTest ()
{
    autopilotArgv.push_back (autopilot);
    autopilotArgv.push_back (runOpt);
    autopilotArgv.push_back (dashV);
    autopilotArgv.push_back (GetParam ());
    autopilotArgv.push_back (NULL);
}

const char **
CompizAutopilotAcceptanceTest::GetAutopilotArgv ()
{
    return &autopilotArgv[0];
}

namespace
{
    std::string FdToString (int fd)
    {
        std::string output;

        int bufferSize = 4096;
        char buffer[bufferSize];

        ssize_t count = 0;

        do
        {
            struct pollfd pfd;
            pfd.events = POLLIN | POLLERR | POLLHUP;
            pfd.revents = 0;
            pfd.fd = fd;

            /* Check for 10ms if there's anything waiting to be read */
            int nfds = poll (&pfd, 1, 10);

            if (nfds == -1)
                throw std::runtime_error (strerror (errno));

            if (nfds)
            {
                /* Read as much as we have allocated for */
                count = read (fd, (void *) buffer, bufferSize - 1);

                /* Something failed, bail */
                if (count == -1)
                    throw std::runtime_error (strerror (errno));

                /* Always null-terminate */
                buffer[count] = '\0';

                /* Add it to the output */
                output += buffer;
            }
            else
            {
                /* There's nothing on the pipe, assume EOF */
                count = 0;
            }

            /* Keep going until there's nothing left */
        } while (count != 0);

        return output;
    }
}

void
CompizAutopilotAcceptanceTest::PrintChildStderr ()
{
    std::string output = FdToString (childStderrPipe.ReadEnd ());

    std::cout << "[== TEST ERRORS ==]" << std::endl
              << output
              << std::endl;
}

void
CompizAutopilotAcceptanceTest::PrintChildStdout ()
{
    std::string output = FdToString (childStdoutPipe.ReadEnd ());

    std::cout << "[== TEST MESSAGES ==]" << std::endl
              << output
              << std::endl;
}

TEST_P (CompizAutopilotAcceptanceTest, AutopilotTest)
{
    std::string scopedTraceMsg ("Running Autopilot Test");
    scopedTraceMsg += GetParam ();

    int status = launchBinaryAndWaitForReturn (std::string (autopilot),
                                               GetAutopilotArgv (),
                                               childStderrPipe.WriteEnd (),
                                               childStdoutPipe.WriteEnd ());

    EXPECT_EQ (status, 0) << "expected exit status of 0";

    if (status)
    {
        PrintChildStdout ();
        PrintChildStderr ();
    }
    else
    {
        /* Extra space here to align with gtest output */
        std::cout << "[AUTOPILOT ] Pass test " << GetParam () << std::endl;
    }
}

INSTANTIATE_TEST_CASE_P (UnityIntegrationAutopilotTests, CompizAutopilotAcceptanceTest,
                         ValuesIn (AutopilotTests));
