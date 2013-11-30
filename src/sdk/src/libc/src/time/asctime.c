
 

#include <time.h>

static char asctime_buffer[ 32 ];

char* asctime( const tm_t* tm ) {
    return asctime_r( tm, asctime_buffer );
}
