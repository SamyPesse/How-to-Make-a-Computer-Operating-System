
 

#include <ctype.h>
#include <errno.h>
#include <limits.h>
#include <stdlib.h>

#if __WORDSIZE == 64
#define ABS_LONG_MIN 9223372036854775808UL
#else
#define ABS_LONG_MIN 2147483648UL
#endif

long int strtol( const char* nptr, char** endptr, int base ) {
    int neg = 0;
    unsigned long int v;
    const char* orig = nptr;

    while ( isspace( *nptr ) ) {
        nptr++;
    }

    if ( ( *nptr == '-' ) && ( isalnum( nptr[ 1 ] ) ) ) {
        neg = -1;
        ++nptr;
    }

    v = strtoul( nptr, endptr, base );

    if ( ( endptr ) && ( *endptr == nptr) ) {
        *endptr = ( char* )orig;
    }

    if ( v >= ABS_LONG_MIN ) {
        if ( ( v == ABS_LONG_MIN ) && ( neg ) ) {
            return v;
        }

        return ( neg ? LONG_MIN : LONG_MAX );
    }

    return ( neg ? -v : v );
}
