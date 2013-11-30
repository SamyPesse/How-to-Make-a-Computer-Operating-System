
 

#include <string.h>

char* strcat( char* d, const char* s ) {
  char* tmp = d;

  while ( *d ) d++;
  while ( ( *d++ = *s++ ) != 0 ) ;

  return tmp;
}
