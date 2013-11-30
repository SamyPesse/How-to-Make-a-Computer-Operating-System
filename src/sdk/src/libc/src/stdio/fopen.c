
 

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

int __parse_mode( const char* mode ) {
    int mode_flags = 0;

    for ( ;; ) {
        switch ( *mode ) {
            case 0 : return mode_flags;
            case 'b': break;
            case 'r': mode_flags = O_RDONLY; break;
            case 'w': mode_flags = O_WRONLY | O_CREAT | O_TRUNC; break;
            case 'a': mode_flags = O_WRONLY | O_CREAT | O_APPEND; break;
            case '+': mode_flags = ( mode_flags & ( ~O_WRONLY ) ) | O_RDWR; break;
            default : break;
        }

        ++mode;
    }
}

FILE* __init_file( int fd, int close_on_error, int mode ) {
    FILE* stream;

    stream = ( FILE* )malloc( sizeof( FILE ) );

    if ( stream == NULL ) {
        if ( close_on_error ) {
            close( fd );
        }

        return NULL;
    }

    stream->buffer = ( char* )malloc( _IO_BUFSIZE );

    if ( stream->buffer == NULL ) {
        free( stream );

        if ( close_on_error ) {
              close( fd );
        }

        return NULL;
    }

    stream->fd = fd;
    stream->flags = 0;
    stream->buffer_pos = 0;
    stream->buffer_size = _IO_BUFSIZE;
    stream->buffer_data_size = 0;

    switch ( mode & O_RDWR ) {
        case O_RDWR :   stream->flags |= ( __FILE_CAN_WRITE | __FILE_CAN_READ ); break;
        case O_RDONLY : stream->flags |= __FILE_CAN_READ; break;
        case O_WRONLY : stream->flags |= __FILE_CAN_WRITE; break;
        default : break;
    }

    stream->has_ungotten = 0;

    return stream;
}

FILE* fopen( const char* path, const char* mode ) {
    int fd;
    int flags;

    flags = __parse_mode( mode );

    fd = open( path, flags, 0666 );

    if ( fd < 0 ) {
        return NULL;
    }

    return __init_file( fd, 1, flags );
}
