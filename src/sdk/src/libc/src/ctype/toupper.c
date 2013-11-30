
 
#include <ctype.h>

int toupper( int c ) {
    if ( islower( c ) ) {
        return c & ~0x20;
    } else {
        return c;
    }
}

ldiv_t ldiv(long numerator, long denominator) {
  ldiv_t x;
  x.quot=numerator/denominator;
  x.rem=numerator-x.quot*denominator;
  return x;
}

div_t div(int numerator, int denominator) {
  div_t x;
  x.quot=numerator/denominator;
  x.rem=numerator-x.quot*denominator;
  return x;
}
