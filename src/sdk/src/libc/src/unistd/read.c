
 

#include <errno.h>
#include <unistd.h>

#include <os.h>

ssize_t read( int fd, void* buf, size_t count ) {
    int error;

    error = syscall3( SYS_read, fd, ( int )buf, count );

    if ( error < 0 ) {
        errno = -error;
        return -1;
    }

    return error;
}
