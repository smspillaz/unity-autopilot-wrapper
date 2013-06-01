/*
 * fdbackup.h
 *
 * Utility class to save file descriptor names and restore them
 * later
 *
 * See LICENSE.md for Copyright information
 */
#ifndef UAW_FDBACKUP_H
#define UAW_FDBACKUP_H

namespace unity
{
    namespace autopilot_wrapper
    {
        class FDBackup
        {
            public:

                FDBackup (int fd);
                ~FDBackup ();

            private:

                FDBackup (FDBackup const &) = delete;
                FDBackup (FDBackup &&) = delete;
                FDBackup & operator= (FDBackup const &) = delete;

                int mOriginalFd;
                int mBackupFd;
        };
    }
}

#endif
