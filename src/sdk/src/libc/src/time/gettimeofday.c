
 

#include <sys/time.h>

#include <os.h>

int gettimeofday( struct timeval* tv, struct timezone* tz ) {
    int ret;
    uint64_t time;

    ret = syscall1( SYS_get_system_time, ( int )&time );

    if ( ret >= 0 ) {
        if ( tv != NULL ) {
            tv->tv_sec = time / 1000000;
            tv->tv_usec = time % 1000000;
        }
    }

    return ret;
}
