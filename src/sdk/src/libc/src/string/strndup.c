
 

#include <stdlib.h>
#include <string.h>
#include <sys/param.h>

char* strndup( const char* s, size_t n ) {
    char* s2;
    size_t len;

    len = strlen( s );
    len = MIN( len, n );

    s2 = ( char* )malloc( len + 1 );

    if ( s2 == NULL ) {
        return NULL;
    }

    memcpy( s2, s, len );
    s2[ len ] = '\0';

    return s2;
}
