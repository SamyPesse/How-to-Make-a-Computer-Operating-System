
 

#include <errno.h>
#include <unistd.h>

#include <os.h>

int dup( int old_fd ) {
    int error;

    error = syscall1( SYS_dup, old_fd );

    if ( error < 0 ) {
        errno = -error;
        return -1;
    }

    return error;
}
