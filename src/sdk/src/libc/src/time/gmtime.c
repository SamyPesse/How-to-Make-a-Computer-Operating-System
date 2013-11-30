
 

#include <time.h>

static tm_t ret;

tm_t* gmtime( const time_t* timep ) {
    return gmtime_r( timep, &ret );
}
