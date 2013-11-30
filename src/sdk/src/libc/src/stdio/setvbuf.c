
 

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>

static int set_flags( FILE* stream, int flags ) {
    switch ( flags ) {
        case _IONBF :
            stream->flags = ( stream->flags & ~( __FILE_BUFLINEWISE ) ) | __FILE_NOBUF;
            return 0;

        case _IOLBF :
            stream->flags = ( stream->flags & ~( __FILE_NOBUF ) ) | __FILE_BUFLINEWISE;
            return 0;

        case _IOFBF :
            stream->flags = stream->flags & ~( __FILE_NOBUF | __FILE_BUFLINEWISE );
            return 0;

        default :
            return -1;
    }
}

int setvbuf( FILE* stream, char* buf, int flags, size_t size ) {
    if ( buf != NULL ) {
        if ( ( stream->flags & __FILE_DONTFREEBUF ) == 0 ) {
            free( stream->buffer );
        }

        stream->buffer = buf;
        stream->flags |= __FILE_DONTFREEBUF;
    } else {
        char *tmp;

        if ( size == 0 ) {
            return set_flags( stream, flags );
        }

        tmp = ( char* )malloc( size );

        if ( tmp == NULL ) {
            return -1;
        }

        if ( ( stream->flags & __FILE_DONTFREEBUF ) == 0 ) {
            free( stream->buffer );
        }

        stream->buffer = tmp;
        stream->flags &= ~__FILE_DONTFREEBUF;
    }

    stream->buffer_size = size;
    stream->buffer_pos = 0;
    stream->buffer_data_size = 0;

    return set_flags( stream, flags );
}
