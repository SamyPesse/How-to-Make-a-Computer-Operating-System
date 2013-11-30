
 

#include <errno.h>
#include <unistd.h>

#include <os.h>

int dup2( int old_fd, int new_fd ) {
    int error;

    error = syscall2( SYS_dup2, old_fd, new_fd );

    if ( error < 0 ) {
        errno = -error;
        return -1;
    }

    return error;
}
