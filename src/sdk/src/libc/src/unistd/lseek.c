
 

#include <errno.h>
#include <unistd.h>

#include <os.h>

off_t lseek( int fd, off_t offset, int whence ) {
    int error;
    off_t result;

    error = syscall4( SYS_lseek, fd, ( int )&offset, whence, ( int )&result );

    if ( error < 0 ) {
        errno = -error;
        return ( off_t )-1;
    }

    return result;
}
