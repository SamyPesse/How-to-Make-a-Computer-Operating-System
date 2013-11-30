
 

#ifndef _MATH_H_
#define _MATH_H_

#define HUGE_VAL \
  (__extension__                                                              \
   ((union { unsigned __l __attribute__((__mode__(__DI__))); double __d; })   \
    { __l: 0x7ff0000000000000ULL }).__d)

int finite( double x );

double sin( double x );
double cos( double x );
double log( double x );
double log10( double x );
double exp( double x );
double floor( double x );
double ceil( double x );
double frexp( double x, int* exp );
double fabs( double x );
double fmod( double x, double y );
double atan2( double y, double x );
double hypot( double x, double y );
double pow( double x, double y );
double ldexp( double x, int exp );
double scalbn( double x, int exp );
double modf( double x, double* iptr );

#endif // _MATH_H_
