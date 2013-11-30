
 

#include <errno.h>
#include <unistd.h>

#include <os.h>

int unlink( const char* pathname ) {
    int error;

    error = syscall1( SYS_unlink, ( int )pathname );

    if ( error < 0 ) {
        errno = -error;
        return -1;
    }

    return 0;
}
