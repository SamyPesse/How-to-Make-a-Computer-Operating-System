
 

#include <dirent.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>

int closedir( DIR* dir ) {
    if ( dir == NULL ) {
        errno = EBADF;
        return -1;
    }

    close( dir->fd );
    free( dir );

    return 0;
}
