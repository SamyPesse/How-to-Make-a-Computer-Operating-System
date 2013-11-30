
 

#include <math.h>
#include <errno.h>

double ldexp( double value, int exp ) {
    if ( !finite(value) || value == 0.0 ) return value;
    value = scalbn(value,exp);
    if ( !finite(value) || value == 0.0 ) errno = ERANGE;
    return value;
}
