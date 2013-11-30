
 

#include <stdio.h>
#include <unistd.h>

#include "stdio_internal.h"

int fputc( int c, FILE* stream ) {
    /* Check if we can write to the stream */

    if ( ( ( stream->flags & __FILE_CAN_WRITE ) == 0 ) ||
         ( __set_stream_flags( stream, 0 ) ) ) {
        stream->flags |= __FILE_ERROR;
        return EOF;
    }

    /* Make sure we have free space in the buffer */

    if ( stream->buffer_pos >= stream->buffer_size - 1 ) {
        if ( fflush( stream ) ) {
            stream->flags |= __FILE_ERROR;
            return EOF;
        }
    }

    if ( stream->flags & __FILE_NOBUF ) {
        if ( write( stream->fd, &c, 1 ) != 1 ) {
            stream->flags |= __FILE_ERROR;
            return EOF;
        }

        return 0;
    }

    stream->buffer[ stream->buffer_pos++ ] = c;

    if ( ( ( stream->flags & __FILE_BUFLINEWISE ) && ( c == '\n' ) ) ||
         ( stream->flags & __FILE_NOBUF ) ) {
        if ( fflush( stream ) ) {
            stream->flags |= __FILE_ERROR;
            return EOF;
        }
    }

    return 0;
}
