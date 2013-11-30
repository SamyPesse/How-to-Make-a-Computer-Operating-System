
 

#undef assert

#ifdef NDEBUG
#define assert(expr) ((void)0)
#else
#define assert(expr) \
    if ( !(expr) ) { __assert_fail( #expr, __FILE__, __LINE__ ); }
#endif /* NDEBUG */

#ifndef _ASSERT_H_
#define _ASSERT_H_

#include <stdio.h>
#include <stdlib.h>

static inline void __assert_fail( const char* expr, const char* file, int line ) {
    printf( "Assertion (%s) failed at %s:%d\n", expr, file, line );
    abort();
}

#endif /* _ASSERT_H_ */
