
 

#include <time.h>

#include "time_int.h"

tm_t* gmtime_r( const time_t* timep, tm_t* result ) {
    if ( _gmtime( *timep, result ) < 0 ) {
        return NULL;
    }

    return result;
}
