
 

#include <errno.h>
#include <unistd.h>

#include <os.h>

int fchdir( int fd ) {
    int error;

    error = syscall1( SYS_fchdir, fd );

    if ( error < 0 ) {
        errno = -error;
        return -1;
    }

    return 0;
}
