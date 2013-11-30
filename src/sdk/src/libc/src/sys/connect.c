
 

#include <errno.h>
#include <sys/socket.h>

#include <os.h>

int connect( int fd, const struct sockaddr* address, socklen_t addrlen ) {
    int error;

    error = syscall3( SYS_connect, fd, ( int )address, addrlen );

    if ( error < 0 ) {
        errno = -error;
        return -1;
    }

    return 0;
}
