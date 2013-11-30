#include <unistd.h>
#include <stdio.h>

int gethostname( char* name, size_t len ) {
    /* TODO */

    snprintf( name, len, "localhost" );

    return 0;
}
