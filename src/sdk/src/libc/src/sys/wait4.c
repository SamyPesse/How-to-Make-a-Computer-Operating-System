
 

#include <errno.h>
#include <sys/wait.h>

#include <os.h>

pid_t wait4( pid_t pid, int* status, int options, struct rusage* rusage ) {
    int error;

    error = syscall4(
        SYS_wait4,
        pid,
        ( int )status,
        options,
        ( int )rusage
    );

    if ( error < 0 ) {
        errno = -error;
        return -1;
    }

    return error;
}
