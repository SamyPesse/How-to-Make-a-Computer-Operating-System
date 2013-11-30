
 
#include <time.h>

static tm_t ret;

tm_t* localtime( const time_t* timep ) {
    gmtime_r( timep, &ret );
    /* TODO: timezones, tzset(3), tzname, etc */
    return &ret;
}
