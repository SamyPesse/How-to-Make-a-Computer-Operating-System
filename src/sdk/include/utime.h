
 

#ifndef _UTIME_H_
#define _UTIME_H_

#include <time.h>

struct utimbuf {
    time_t actime; /* access time */
    time_t modtime; /* modification time */
};

int utime( const char* filename, const struct utimbuf* times );
int utimes( const char* filename, const timeval_t times[2] );

#endif // _UTIME_H_
