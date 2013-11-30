
 

#include <stdio.h>



int fpurge( FILE* stream ) {
    if ( stream->flags & __FILE_NOBUF ) {
        return 0;
    }

    stream->has_ungotten = 0;

    if ( stream->flags & __FILE_BUFINPUT ) {
        stream->buffer_pos = stream->buffer_data_size;
    } else {
        stream->buffer_pos = 0;
    }

    return 0;
}
