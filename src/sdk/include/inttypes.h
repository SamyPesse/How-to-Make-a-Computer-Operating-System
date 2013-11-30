
 

#ifndef _INTTYPES_H_
#define _INTTYPES_H_

#include <stdint.h>

intmax_t strtoimax( const char *nptr, char** endptr, int base );
uintmax_t strtoumax( const char *nptr, char** endptr, int base );

#endif /* _INTTYPES_H_ */
