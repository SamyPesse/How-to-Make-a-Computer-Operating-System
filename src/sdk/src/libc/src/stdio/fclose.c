
 

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int fclose( FILE* stream ) {
    int result;

    result = fflush( stream );
    result |= close( stream->fd );

    if ( ( ( stream->flags & __FILE_DONTFREEBUF ) == 0 ) &&
         ( stream->buffer != NULL ) ) {
        free( stream->buffer );
    }

    free( stream );

    return result;
}
