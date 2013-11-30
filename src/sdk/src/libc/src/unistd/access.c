#include <unistd.h>
#include <errno.h>
#include <os.h>

int access( const char* pathname, int mode ) {
    int error;

    error = syscall2(
        SYS_access,
        ( int )pathname,
        mode
    );

    if ( error < 0 ) {
        errno = -error;
        return -1;
    }

    return 0;
}
