
 

#include <signal.h>
#include <errno.h>

int sigaddset( sigset_t* set, int signum ) {
    if ( ( set == NULL ) ||
         ( signum < 1 ) ||
         ( signum >= _NSIG ) ) {
        errno = -EINVAL;
        return -1;
    }

    *set |= ( 1ULL << ( signum - 1 ) );

    return 0;
}
