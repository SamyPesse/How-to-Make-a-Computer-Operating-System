
 

#include <errno.h>
#include <sys/mount.h>

#include <os.h>

int umount(
    const char* dir
) {
    int error;

    error = syscall1(
        SYS_unmount,
        ( int )dir
    );

    if ( error < 0 ) {
        errno = -error;
        return -1;
    }

    return 0;
}
