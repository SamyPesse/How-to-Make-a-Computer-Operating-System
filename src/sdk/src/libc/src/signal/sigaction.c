
 

#include <errno.h>
#include <signal.h>

#include <os.h>

int sigaction( int signum, const struct sigaction* act, struct sigaction* oldact ) {
    int error;

    error = syscall3(
        SYS_sigaction,
        signum,
        ( int )act,
        ( int )oldact
    );

    if ( error < 0 ) {
        errno = -error;
        return -1;
    }

    return 0;
}
