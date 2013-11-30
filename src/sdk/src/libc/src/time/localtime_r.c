
 

#include <time.h>

tm_t* localtime_r( const time_t* timep, tm_t* result ) {
    gmtime_r( timep, result );
    return result;
}
