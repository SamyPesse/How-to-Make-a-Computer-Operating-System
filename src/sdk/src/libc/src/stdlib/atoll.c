
 

#include <ctype.h>
#include <stdlib.h>

long long int atoll( const char* s ) {
    long long int v = 0;
    int sign = 1;

    while ( *s == ' '  ||  ( unsigned int )( *s - 9 ) < 5u ) {
        ++s;
    }

    switch ( *s ) {
        case '-': sign = -1;
        case '+': ++s;
    }

    while ( ( unsigned int )( *s - '0' ) < 10u ) {
        v=  v * 10 + *s - '0';
        ++s;
    }

    return sign == -1 ? -v : v;
}
