
 

#include <errno.h>
#include <utime.h>

#include <os.h>

int utimes( const char* filename, const timeval_t times[2] ) {
    struct utimbuf tmp;

    /* NOTE: no microsecond precision */
    tmp.actime = times[ 0 ].tv_sec;
    tmp.modtime = times[ 1 ].tv_sec;

    /* This is a wrapper around utime() */
    return utime( filename, &tmp );
}
