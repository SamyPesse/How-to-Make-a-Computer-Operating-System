
 

#include <signal.h>
#include <errno.h>

#include <os.h>

int kill( pid_t pid, int signal ) {
    int error;

    error = syscall2(
        SYS_kill,
        pid,
        signal
    );

    if ( error < 0 ) {
        errno = -error;
        return -1;
    }

    return 0;
}
