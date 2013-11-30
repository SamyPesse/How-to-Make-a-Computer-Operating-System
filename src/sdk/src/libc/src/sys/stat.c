
 
#include <errno.h>
#include <sys/stat.h>

#include <os.h>

int stat( const char* path, struct stat* stat ) {
    int error;

    error = syscall2( SYS_stat, ( int )path, ( int )stat );

    if ( error < 0 ) {
        errno = -error;
        return -1;
    }

    return 0;
}
