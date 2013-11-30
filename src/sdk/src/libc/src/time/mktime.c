
 

#include <time.h>

#include "time_int.h"

time_t mktime( tm_t* tm ) {
    if ( tm->tm_year > 2100 ) {
        return -1;
    }

    return daysdiff( tm->tm_year, tm->tm_mon, tm->tm_mday ) * SECONDS_PER_DAY +
           tm->tm_hour * SECONDS_PER_HOUR + tm->tm_min * SECONDS_PER_MINUTE + tm->tm_sec;
}
