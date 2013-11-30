
 

#include <signal.h>
#include <errno.h>

sighandler_t signal( int signum, sighandler_t handler ) {
    int error;
    struct sigaction act;
    struct sigaction oldact;

    if ( ( handler == SIG_ERR ) ||
         ( signum < 0 ) ||
         ( signum >= _NSIG ) ) {
        errno = -EINVAL;
        return SIG_ERR;
    }

    act.sa_handler = handler;

    error = sigemptyset( &act.sa_mask );

    if ( error < 0 ) {
        return SIG_ERR;
    }

    error = sigaddset( &act.sa_mask, signum );

    if ( error < 0 ) {
        return SIG_ERR;
    }

    act.sa_flags = SA_RESTART;

    if ( sigaction( signum, &act, &oldact ) < 0 ) {
        return SIG_ERR;
    }

    return oldact.sa_handler;
}
