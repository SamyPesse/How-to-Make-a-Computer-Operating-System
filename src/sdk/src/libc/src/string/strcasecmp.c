
 

#include <string.h>
#include <ctype.h>

int strcasecmp( const char* s1, const char* s2 ) {
    int result;

    while ( 1 ) {
        result = tolower( *s1 ) - tolower( *s2++ );

        if ( ( result != 0 ) || ( *s1++ == 0 ) ) {
            break;
        }
    }

    return result;
}
