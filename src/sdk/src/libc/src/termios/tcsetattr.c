
 

#include <termios.h>
#include <errno.h>
#include <stddef.h>
#include <sys/ioctl.h>

int tcsetattr( int fd, int optional_actions, const struct termios* tio ) {
    int error;

    if ( tio == NULL ) {
        errno = EINVAL;
        return -1;
    }

    switch ( optional_actions ) {
        case TCSANOW :
            error = ioctl( fd, TCSETA, tio );
            break;

        case TCSADRAIN :
            error = ioctl( fd, TCSETAW, tio );
            break;

        case TCSAFLUSH :
            error = ioctl( fd, TCSETAF, tio );
            break;

        default :
            error = -EINVAL;
            break;
    }

    if ( error < 0 ) {
        errno = -error;
        return -1;
    }

    return 0;
}
