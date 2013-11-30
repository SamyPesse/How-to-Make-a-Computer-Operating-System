
 

#include <time.h>
#include <errno.h>
#include <sys/types.h>

#include <os.h>

int nanosleep( const struct timespec* req, struct timespec* rem ) {
    int error;
    uint64_t microsecs;
    uint64_t remaining;

    microsecs = ( uint64_t )req->tv_sec * 1000000 + ( uint64_t )req->tv_nsec / 1000;

    if ( microsecs == 0 ) {
        microsecs = 1;
    }

    error = syscall2( SYS_sleep_thread, ( int )&microsecs, ( int )&remaining );

    if ( error < 0 ) {
        errno = -error;

        if ( rem != NULL ) {
            rem->tv_sec = remaining / 1000000;
            rem->tv_nsec = ( remaining % 1000000 ) * 1000;
        }

        return -1;
    }

    return 0;
}
