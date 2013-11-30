
 

#include <string.h>

char* strncat( char* d, const char* s, size_t c ) {
  char* tmp = d;

  if ( c > 0 ) {
    while ( *d ) d++;
    while ( ( *d++ = *s++ ) ) {
      if ( --c == 0 ) {
        *d = 0;
        break;
      }
    }
  }

  return tmp;
}
