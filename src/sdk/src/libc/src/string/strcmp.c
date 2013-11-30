
 

#include <string.h>

int strcmp( const char* s1, const char* s2 ) {
    int result;

    while ( 1 ) {
        result = *s1 - *s2++;

        if ( ( result != 0 ) || ( *s1++ == 0 ) ) {
            break;
        }
    }

    return result;
}
