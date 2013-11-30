
 

#include <ctype.h>

int isgraph( int c ) {
    if ( c == ' ' ) {
        return 0;
    }

    return isprint( c );
}
