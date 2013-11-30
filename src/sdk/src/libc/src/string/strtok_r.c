
 

#include <string.h>

char* strtok_r( char* s, const char* delim, char** ptrptr ) {
    char* tmp = NULL;

    if ( s == NULL ) {
        s = *ptrptr;
    }

    s += strspn( s, delim );

    if ( *s ) {
        tmp = s;
        s += strcspn( s, delim );

        if ( *s ) {
            *s++ = 0;
        }
    }

    *ptrptr = s;

    return tmp;
}
