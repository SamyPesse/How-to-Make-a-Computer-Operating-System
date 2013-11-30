
 

#include <errno.h>
#include <utime.h>

#include <os.h>

int utime( const char* filename, const struct utimbuf* times ) {
    int error;
    struct utimbuf current;

    if ( times == NULL ) {
        current.actime = time( NULL );
        current.modtime = current.actime;

        times = ( const struct utimbuf* )&current;
    }

    error = syscall2( SYS_utime, ( int )filename, ( int )times  );

    if ( error < 0 ) {
        errno = -error;
        return -1;
    }

    return 0;
}
