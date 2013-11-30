
 

#include <errno.h>
#include <sys/time.h>

#include <os.h>

int stime( time_t *t ) {
    int error;

    error = syscall1( SYS_stime, ( int )t );

    if ( error < 0 ) {
        errno = -error;
        return -1;
    }

    return 0;
}
