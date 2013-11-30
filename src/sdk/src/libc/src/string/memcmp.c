
 

#include <string.h>

int memcmp( const void* p1, const void* p2, size_t c ) {
    const unsigned char* su1, *su2;
    signed char res = 0;

    for ( su1 = p1, su2 = p2; 0 < c; ++su1, ++su2, c-- ) {
        if ( ( res = *su1 - *su2 ) != 0 ) {
            break;
        }
    }

    return res;
}
