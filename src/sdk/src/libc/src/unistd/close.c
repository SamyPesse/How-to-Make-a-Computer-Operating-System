
 

#include <errno.h>
#include <unistd.h>

#include <os.h>

int close( int fd ) {
    int error;

    error = syscall1( SYS_close, fd );

    if ( error < 0 ) {
        errno = -error;
        return -1;
    }

    return 0;
}
