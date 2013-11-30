
 

#include <string.h>

static char* strtok_pos;

char* strtok( char* s, const char* delim ) {
    return strtok_r( s, delim, &strtok_pos );
}
