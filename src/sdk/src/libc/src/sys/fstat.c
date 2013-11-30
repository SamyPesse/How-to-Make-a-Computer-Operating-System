
 

#include <errno.h>
#include <sys/stat.h>

#include <os.h>

int fstat( int fd, struct stat* stat ) {
    int error;

    error = syscall2( SYS_fstat, fd, ( int )stat );

    if ( error < 0 ) {
        errno = -error;
        return -1;
    }

    return 0;
}
