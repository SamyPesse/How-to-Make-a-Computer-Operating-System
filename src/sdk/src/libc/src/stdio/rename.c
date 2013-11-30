
 

#include <errno.h>
#include <unistd.h>


int rename( const char* oldpath, const char* newpath ) {
    printf( "TODO: rename not yet implemented! (from: %s to: %s)\n", oldpath, newpath );

    errno = -ENOSYS;

    return -1;
}
