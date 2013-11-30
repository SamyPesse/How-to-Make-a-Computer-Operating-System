
 

#include <stdio.h>
#include <unistd.h>

int fputs( const char* s, FILE* stream ) {
    while ( *s ) {
        fputc( *s++, stream );
    }

    fflush( stream );

    return 0;
}
