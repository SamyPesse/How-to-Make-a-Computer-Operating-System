
 

#include <stdio.h>

#include "stdio_internal.h"

int __set_stream_flags( FILE* stream, int new_flags ) {
    if ( ( stream->flags & __FILE_BUFINPUT ) != new_flags) {
        int error;

        error = fflush( stream );

        stream->flags = ( stream->flags & ~__FILE_BUFINPUT ) | new_flags;

        return error;
    }

    return 0;
}
