
 

#include <errno.h>
#include <sys/socket.h>

#include <os.h>

int socket( int domain, int type, int protocol ) {
    int error;

    error = syscall3( SYS_socket, domain, type, protocol );

    if ( error < 0 ) {
        errno = -error;
        return -1;
    }

    return error;
}
