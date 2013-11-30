
 

#include <ctype.h>

int toascii( int c ) {
    return ( c & ~0x80 );
}
