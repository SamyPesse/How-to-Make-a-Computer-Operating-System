
 

#include <stdio.h>
#include <errno.h>
#include <fcntl.h>
#include <unistd.h>

int __parse_mode( const char* mode );

FILE* freopen( const char* path, const char* mode, FILE* stream ) {
    int flags;

    if ( stream == NULL ) {
        errno = -EINVAL;
        return NULL;
    }

    flags = __parse_mode( mode );

    fflush( stream );
    close( stream->fd );

    stream->fd = open( path, flags, 0666 );

    if ( stream->fd != -1 ) {
        stream->flags = 0;

        switch ( flags & 3 ) {
          case O_RDWR :   stream->flags |= ( __FILE_CAN_READ | __FILE_CAN_WRITE ); break;
          case O_RDONLY : stream->flags |= __FILE_CAN_READ; break;
          case O_WRONLY : stream->flags |= __FILE_CAN_WRITE; break;
        }
    }

    return stream;
}
