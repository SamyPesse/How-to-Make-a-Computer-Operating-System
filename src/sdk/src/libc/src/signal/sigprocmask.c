
 

#include <signal.h>
#include <errno.h>

#include <os.h>

int sigprocmask( int how, const sigset_t* set, sigset_t* oldset ) {
    int error;

    error = syscall3(
        SYS_sigprocmask,
        how,
        ( int )set,
        ( int )oldset
    );

    if ( error < 0 ) {
        errno = -error;
        return -1;
    }

    return 0;
}
