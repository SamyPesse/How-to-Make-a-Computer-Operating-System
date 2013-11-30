#include <errno.h>
#include <unistd.h>

#include <os.h>

ssize_t write( int fd, const void* buf, size_t count ) {
    int error;

    error = syscall3( SYS_write, fd, ( int )buf, count );

    if ( error < 0 ) {
        errno = -error;
        return -1;
    }

    return error;
}
