
 

#include <ctype.h>

int isspace( int c ) {
    return ( c == '\t' || c == '\n' || c == '\v' || c == '\f' || c == '\r' || c == ' ' );
}
