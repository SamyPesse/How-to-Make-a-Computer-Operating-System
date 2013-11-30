
 

#include <string.h>
#include <ctype.h>

int strncasecmp( const char* s1, const char* s2, size_t c ) {
    int result = 0;

    while ( c ) {
        result = toupper( *s1 ) - toupper( *s2++ );

        if ( ( result != 0 ) || ( *s1++ == 0 ) ) {
            break;
        }

        c--;
    }

    return result;
}
