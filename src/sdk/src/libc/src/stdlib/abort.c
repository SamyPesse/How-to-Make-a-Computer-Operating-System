
 

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void abort( void ) {
    fprintf( stderr, "Application aborted!\n" );
    exit( -1 );
}
