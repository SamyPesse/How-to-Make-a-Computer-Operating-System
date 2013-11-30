
 

#include <string.h>

char* strrchr( const char* s, int c ) {
  const char* end = s + strlen( s );

  do {
    if ( *end == ( char )c ) {
      return ( char * )end;
    }
  } while ( --end >= s );

  return NULL;
}
