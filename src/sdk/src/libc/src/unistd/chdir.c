
 

#include <errno.h>
#include <unistd.h>

#include <os.h>

int chdir( const char* path ) {
    int error;

    error = syscall1( SYS_chdir, ( int )path );

    if ( error < 0 ) {
        errno = -error;
        return -1;
    }

    return 0;
}
