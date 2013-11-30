
 

#include <ctype.h>
#include <stdlib.h>
#include <limits.h>
#include <errno.h>
#include <inttypes.h>

long long int strtoll( const char* nptr, char** endptr, int base ) {
  int neg = 0;
  unsigned long long int v;
  const char* orig = nptr;

  while ( isspace( *nptr ) ) {
      nptr++;
  }

  if ( *nptr == '-' && isalnum( nptr[ 1 ] ) ) {
      neg = -1;
      nptr++;
  }

  v = strtoull( nptr, endptr, base );

  if ( endptr && *endptr == nptr ) {
      *endptr = ( char* )orig;
  }

  if ( v > LLONG_MAX ) {
    if ( v == 0x8000000000000000ull && neg ) {
      errno = 0;
      return v;
    }

    errno=ERANGE;

    return ( neg ? LLONG_MIN : LLONG_MAX );
  }

  return ( neg ? -v : v );
}

intmax_t strtoimax( const char* nptr, char** endptr, int base )	__attribute__(( alias( "strtoll" ) ));
