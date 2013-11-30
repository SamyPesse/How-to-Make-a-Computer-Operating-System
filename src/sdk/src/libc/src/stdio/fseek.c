
 

#include <stdio.h>
#include <unistd.h>

int fseeko( FILE* stream, off_t offset, int whence ) {
    fflush( stream );

    stream->buffer_pos = 0;
    stream->buffer_data_size = 0;
    stream->flags &= ~( __FILE_EOF | __FILE_ERROR );
    stream->has_ungotten = 0;

    return ( lseek( stream->fd, offset, whence ) != -1 ? 0 : -1 );
}

int fseek( FILE* stream, long offset, int whence ) {
    return fseeko( stream, ( off_t )offset, whence );
}
