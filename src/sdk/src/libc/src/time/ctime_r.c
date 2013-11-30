
 

#include <time.h>

char* ctime_r( const time_t* timep, char *buf) {
    buf = asctime( localtime( timep ) );

    return buf;
}
