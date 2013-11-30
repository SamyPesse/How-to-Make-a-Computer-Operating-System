
 
#include <stdlib.h>

void* bsearch( const void* key, const void* base, size_t nmemb, size_t size, int ( *compare )( const void*, const void* ) ) {
    size_t m;

    while ( nmemb ) {
        int tmp;
        void* p;

        m = nmemb / 2;
        p = ( void* )( ( ( const char* )base ) + ( m * size ) );

        if ( ( tmp = ( *compare )( key, p ) ) < 0 ) {
            nmemb = m;
        } else if ( tmp > 0 ) {
            base = p + size;
            nmemb -= m + 1;
        } else {
          return p;
        }
    }

    return NULL;
}
