
 

#include <errno.h>
#include <sys/stat.h>

#include <os.h>

int mkdir( const char* pathname, mode_t mode ) {
    int error;

    error = syscall2( SYS_mkdir, ( int )pathname, ( int )mode );

    if ( error < 0 ) {
        errno = -error;
        return -1;
    }

    return 0;
}
