
 

#include <errno.h>
#include <stdio.h>
#include <unistd.h>

#include <os.h>

ssize_t readlink( const char* path, char* buf, size_t bufsiz ) {
    int error;

    error = syscall3( SYS_readlink, ( int )path, ( int )buf, bufsiz );

    if ( error < 0 ) {
        errno = -error;
        return -1;
    }

    return error;
}
