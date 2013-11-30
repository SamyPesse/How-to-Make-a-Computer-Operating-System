
 

#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>

size_t fwrite( const void* ptr, size_t size, size_t nmemb, FILE* stream ) {
    ssize_t res;
    unsigned long len=size * nmemb;
    long i;

    if ( ( stream->flags & __FILE_CAN_WRITE ) == 0 ) {
        stream->flags |= __FILE_ERROR;
        return 0;
    }

    if ( ( nmemb == 0 ) ||
         ( ( len / nmemb ) != size ) ) {
        return 0;
    }

    if ( ( len > stream->buffer_size ) || ( stream->flags & __FILE_NOBUF ) ) {
        if ( fflush( stream ) ) {
            return 0;
        }

        res = write( stream->fd, ptr, len );
    } else {
        register const unsigned char* c = ptr;

        for ( i = len; i > 0; --i, ++c ) {
            if ( fputc( *c, stream ) ) {
                res = len - i;
                goto abort;
            }
        }

        res = len;
    }

    if ( res < 0 ) {
        stream->flags |= __FILE_ERROR;
        return 0;
    }

abort:
    return size ? res / size : 0;
}
