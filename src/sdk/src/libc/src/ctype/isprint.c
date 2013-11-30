
 

#include <ctype.h>

int isprint( int c ) {
    c &= 0x7F;
    return ( ( c >= 0x20 ) && ( c < 0x7F ) );
}
