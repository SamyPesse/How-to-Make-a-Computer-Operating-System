
 

#include <dirent.h>
#include <unistd.h>
#include <errno.h>

struct dirent* readdir( DIR* dir ) {
    int error;

    if ( dir == NULL ) {
        return NULL;
    }

    error = getdents( dir->fd, &dir->entry, sizeof( struct dirent ) );

    if ( error == 0 ) {
        return NULL;
    }

    return &dir->entry;
}

int readdir_r( DIR* dir, struct dirent* entry, struct dirent** result ) {
    int error;

    if ( ( dir == NULL ) ||
         ( entry == NULL ) ) {
        errno = -EINVAL;
        return -1;
    }

    error = getdents( dir->fd, entry, sizeof( struct dirent ) );

    if ( error == 0 ) {
        *result = NULL;
    } else {
        *result = entry;
    }

    return 0;
}
