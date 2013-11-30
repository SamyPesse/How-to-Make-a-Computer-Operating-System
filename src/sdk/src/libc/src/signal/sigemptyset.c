
 

#include <signal.h>
#include <errno.h>

int sigemptyset( sigset_t* set ) {
    if ( set == NULL ) {
        errno = -EINVAL;
        return -1;
    }

    *set = 0;

    return 0;
}

