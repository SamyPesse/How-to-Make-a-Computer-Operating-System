
 

#include <fcntl.h>
#include <errno.h>

#include <os.h>

int open( const char* filename, int flags, ... ) {
    int error;

    error = syscall2( SYS_open, ( int )filename, flags );

    if ( error < 0 ) {
        errno = -error;
        return -1;
    }

    return error;
}
