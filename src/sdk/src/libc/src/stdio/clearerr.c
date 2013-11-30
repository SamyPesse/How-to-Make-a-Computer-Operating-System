
 

#include <stdio.h>

void clearerr( FILE* stream ) {
    stream->flags &= ~( __FILE_EOF | __FILE_ERROR );
}
