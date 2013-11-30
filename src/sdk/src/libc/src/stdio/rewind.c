
 

#include <stdio.h>

void rewind( FILE* stream ) {
    clearerr( stream );
    fseek( stream, 0L, SEEK_SET );
}
