
 

#include <errno.h>
#include <unistd.h>

#include <os.h>

int getdents( int fd, struct dirent* entry, unsigned int count ) {
    int error;

    error = syscall3( SYS_getdents, fd, ( int )entry, count );

    if ( error < 0 ) {
        errno = -error;
        return -1;
    }

    return error;
}
