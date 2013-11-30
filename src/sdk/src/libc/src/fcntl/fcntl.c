
 

#include <errno.h>
#include <fcntl.h>

#include <os.h>

int fcntl( int fd, int cmd, ... ) {
    int error;

    error = syscall3( SYS_fcntl, fd, cmd, *( ( ( int* )&cmd ) + 1 ) );

    if ( error < 0 ) {
        errno = -error;
        return -1;
    }

    return error;
}
