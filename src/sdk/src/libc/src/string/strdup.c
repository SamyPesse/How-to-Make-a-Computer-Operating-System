
 

#include <stdlib.h>
#include <string.h>

char* strdup( const char* s ) {
    char* s2;
    size_t length;

    length = strlen( s );
    s2 = ( char* )malloc( length + 1 );

    if ( s2 == NULL ) {
        return NULL;
    }

    memcpy( s2, s, length + 1 );

    return s2;
}
