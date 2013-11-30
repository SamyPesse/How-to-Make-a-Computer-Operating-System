
 

#include <string.h>

void* memchr( const void* s, int c, size_t n ) {
    const unsigned char* src = ( const unsigned char* )s;
    unsigned char ch = c;

    for ( ; n != 0; n-- ) {
        if ( *src == ch ) {
            return ( void* )src;
        }

        src++;
    }

    return NULL;
}
