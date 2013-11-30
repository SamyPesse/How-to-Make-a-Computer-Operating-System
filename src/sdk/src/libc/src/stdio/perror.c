
 

#include <stdio.h>
#include <string.h>
#include <errno.h>

void perror( const char* s ) {
    if ( s != NULL ) {
        fprintf( stderr, "%s", s );
    }

    fprintf( stderr, ": %s\n", strerror( errno ) );
}
