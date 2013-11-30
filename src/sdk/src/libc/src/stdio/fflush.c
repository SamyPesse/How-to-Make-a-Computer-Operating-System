
 

#include <stdio.h>
#include <unistd.h>

int fflush( FILE* stream ) {
    if ( stream->flags & __FILE_BUFINPUT ) {
        int tmp;

        tmp = ( int )stream->buffer_pos - ( int )stream->buffer_data_size;

        if ( tmp != 0 ) {
            lseek( stream->fd, tmp, SEEK_CUR );
        }

        stream->buffer_pos = 0;
        stream->buffer_data_size = 0;
    } else {
        if ( stream->buffer_pos > 0 ) {
            if ( write( stream->fd, stream->buffer, stream->buffer_pos ) != stream->buffer_pos ) {
				write(0,"\nerror file \n",strlen("\nerror file \n"));
                stream->flags |= __FILE_ERROR;
                return -1;
            }
			memset(stream->buffer,0,_IO_BUFSIZE);
            stream->buffer_pos = 0;
        }
    }

    return 0;
}
