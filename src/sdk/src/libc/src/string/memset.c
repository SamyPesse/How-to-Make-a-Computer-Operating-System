
 

#include <string.h>

void* memset( void* s, int c, size_t n ) {
    char* _src;

    _src = ( char* )s;

    while ( n-- ) {
        *_src++ = c;
    }

    return s;
}
