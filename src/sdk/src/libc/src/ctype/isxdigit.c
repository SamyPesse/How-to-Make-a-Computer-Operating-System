
 

#include <ctype.h>

int isxdigit( int c ) {
    return ( ( ( c >= '0' ) && ( c <= '9' ) ) ||
             ( ( c >= 'a' ) && ( c <= 'f' ) ) ||
             ( ( c >= 'A' ) && ( c <= 'F' ) ) );
}
