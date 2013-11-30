
 

#include <errno.h>
#include <sys/select.h>

#include <os.h>

int select( int fds, fd_set* readfds, fd_set* writefds, fd_set* exceptfds, struct timeval* timeout ) {
    int error;

    error = syscall5(
        SYS_select,
        fds,
        ( int )readfds,
        ( int )writefds,
        ( int )exceptfds,
        ( int )timeout
    );

    if ( error < 0 ) {
        errno = -error;
        return -1;
    }

    return error;
}
