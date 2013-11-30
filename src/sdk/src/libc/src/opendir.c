
 

#include <dirent.h>
#include <stdlib.h>
#include <fcntl.h>

DIR* opendir( const char* name ) {
    DIR* dir;

    dir = ( DIR* )malloc( sizeof( DIR ) );

    if ( dir == NULL ) {
        return NULL;
    }

    dir->fd = open( name, O_RDONLY );

    if ( dir->fd < 0 ) {
        free( dir );
        return NULL;
    }

    return dir;
}
