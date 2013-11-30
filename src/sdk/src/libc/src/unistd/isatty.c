
 

#include <errno.h>
#include <unistd.h>

#include <os.h>

int isatty( int fd ) {
    int error;

    error = syscall1( SYS_isatty, fd );

    if ( error < 0 ) {
        errno = -error;
        return 0;
    }

    return error;
}
