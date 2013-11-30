
 

#include <errno.h>
#include <sys/mount.h>

#include <os.h>

int mount(
    const char* source,
    const char* target,
    const char* filesystemtype,
    unsigned long mountflags,
    const void* data
) {
    int error;

    error = syscall4(
        SYS_mount,
        ( int )source,
        ( int )target,
        ( int )filesystemtype,
        ( int )mountflags
    );

    if ( error < 0 ) {
        errno = -error;
        return -1;
    }

    return 0;
}
