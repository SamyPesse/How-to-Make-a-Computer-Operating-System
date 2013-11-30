
 

#include <signal.h>
#include <errno.h>

int sigismember( const sigset_t* set, int signum ) {
    if ( ( set == NULL ) ||
         ( signum < 1 ) ||
         ( signum >= _NSIG ) ) {
        errno = -EINVAL;
        return -1;
    }

    if ( ( ( *set ) & ( 1ULL << ( signum - 1 ) ) ) != 0 ) {
        return 1;
    }

    return 0;
}
