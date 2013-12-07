


#include <errno.h>
#include <unistd.h>

#include <os.h>

ssize_t pread( int fd, void* buf, size_t count, off_t offset ) {
    int error;

    error = syscall4( SYS_pread, fd, ( int )buf, count, ( int )&offset );

    if ( error < 0 ) {
        errno = -error;
        return -1;
    }

    return error;
}
