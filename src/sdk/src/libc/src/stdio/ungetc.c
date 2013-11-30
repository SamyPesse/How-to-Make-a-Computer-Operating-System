
 
#include <stdio.h>

int ungetc( int c, FILE* stream ) {
    if ( ( stream->has_ungotten ) ||
         ( c < 0 ) ||
         ( c > 255 ) ) {
        return EOF;
    }

    stream->has_ungotten = 1;
    stream->unget_buffer = ( unsigned char )c;
    stream->flags &= ~( __FILE_EOF | __FILE_ERROR );

    return c;
}
