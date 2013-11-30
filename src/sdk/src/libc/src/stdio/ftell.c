
 

#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <limits.h>

off_t ftello( FILE* stream ) {
    off_t l;

    if ( stream->flags & ( __FILE_EOF | __FILE_ERROR ) ) {
        return -1;
    }

    l = lseek( stream->fd, 0, SEEK_CUR );

    if ( l == ( off_t )-1 ) {
        return -1;
    }

    if ( stream->flags & __FILE_BUFINPUT ) {
        return l - ( stream->buffer_data_size - stream->buffer_pos ) - stream->has_ungotten;
    } else {
        return l + stream->buffer_pos;
    }
}

long ftell( FILE* stream ) {
    off_t l;

    l = ftello( stream );

    if ( l > LONG_MAX ) {
        errno = EOVERFLOW;
        return -1;
    }

    return ( long )l;
}
