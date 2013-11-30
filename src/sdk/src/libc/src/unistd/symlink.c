#include <errno.h>
#include <unistd.h>

#include <os.h>

int symlink( const char* oldpath, const char* newpath ) {
    int error;

    error = syscall2( SYS_symlink, ( int )oldpath, ( int )newpath );

    if ( error < 0 ) {
        errno = -error;
        return -1;
    }

    return 0;
}
