
 

#include <string.h>

size_t strlen( const char* s ) {
    size_t r = 0;

    for( ; *s++ != 0; r++ ) { }

    return r;
}
