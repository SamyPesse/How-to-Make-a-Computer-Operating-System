
 

#include <dirent.h>
#include <errno.h>

#include <os.h>

void rewinddir( DIR* dirp ) {
    int error;

    error = syscall1( SYS_rewinddir, dirp->fd );

    if ( error < 0 ) {
        errno = -error;
    }
}
