
 
#include <errno.h>
#include <sys/ioctl.h>

#include <os.h>

int ioctl( int fd, int request, ... ) {
    int error;

    error = syscall3( SYS_ioctl, fd, request, *( ( ( ( int* )&request ) ) + 1 ) );

    if ( error < 0 ) {
        errno = -error;
        return -1;
    }

    return error;
}
