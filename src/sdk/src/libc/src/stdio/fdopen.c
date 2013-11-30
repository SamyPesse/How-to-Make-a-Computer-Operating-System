
 

#include <stdio.h>
#include <errno.h>

int __parse_mode( const char* mode );
FILE* __init_file( int fd, int close_on_error, int mode );

FILE* fdopen( int fd, const char* mode ) {
    int flags;

    if ( fd < 0 ) {
        errno = -EINVAL;
        return NULL;
    }

    flags = __parse_mode( mode );

    return __init_file( fd, 0, flags );
}
