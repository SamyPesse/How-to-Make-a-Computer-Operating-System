
 

#include <errno.h>
#include <unistd.h>

#include <os.h>

int rmdir( const char* pathname ) {
    int error;

    error = syscall1( SYS_rmdir, ( int )pathname );

    if ( error < 0 ) {
        errno = -error;
        return -1;
    }

    return 0;
}
