
 

#include <string.h>

char* strncpy( char* d, const char* s, size_t c ) {
    size_t i;
    char* tmp = d;

    for ( i = 0; i < c; i++ ) {
        *d++ = *s;

        if ( *s++ == 0 ) {
            break;
        }
    }

    for ( ; i < c; i++ ) {
        *d++ = 0;
    }

    return tmp;
}
