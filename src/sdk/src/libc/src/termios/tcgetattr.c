
 

#include <termios.h>
#include <errno.h>
#include <stddef.h>
#include <sys/ioctl.h>

int tcgetattr( int fd, struct termios* tio ) {
    int error;

    if ( tio == NULL ) {
        errno = EINVAL;
        return -1;
    }

    error = ioctl( fd, TCGETA, tio );

    if ( error < 0 ) {
        errno = -error;
        return -1;
    }

    return 0;
}
