
 

#include <time.h>

char* asctime_r( const tm_t* tm, char* buf ) {
    strftime( buf, 26, "%a %b %d %H:%M:%S %Y\n", tm );

    return buf;
}
