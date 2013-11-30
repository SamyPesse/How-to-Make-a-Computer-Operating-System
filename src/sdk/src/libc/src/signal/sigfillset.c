
 

#include <signal.h>
#include <errno.h>
#include <string.h>

int sigfillset( sigset_t* set ) {
    if ( set == NULL ) {
        errno = -EINVAL;
        return -1;
    }

    memset( ( void* )set, 0xFF, sizeof( sigset_t ) );

    return 0;
}
