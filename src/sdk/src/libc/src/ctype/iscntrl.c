
 

#include <ctype.h>

int iscntrl( int c ) {
    return ( ( ( unsigned int )c < 32u ) ||
             ( c == 127 ) );
}
