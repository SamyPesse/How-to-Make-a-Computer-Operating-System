
 

#include <sys/time.h>

#include <os.h>

time_t time( time_t* t ) {
    int ret;
    uint64_t time;

    ret = syscall1( SYS_get_system_time, ( int )&time );

    if ( ret < 0 ) {
        time = 0;
    } else {
        time /= 1000000;
    }

    if ( t != NULL ) {
        *t = time;
    }

    return time;
}
