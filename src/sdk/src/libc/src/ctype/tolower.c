
 

#include <ctype.h>

int tolower( int c ) {
    if ( isupper( c ) ) {
        return c | 0x20;
    } else {
        return c;
    }
}
