#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>

#include <os.h>

typedef void ( *atexit_func_t )( void );

static uint32_t atexit_count = 0;
static atexit_func_t atexit_functions[ ATEXIT_MAX ];

int atexit( void ( *function )( void ) ) {
    if ( atexit_count >= ATEXIT_MAX ) {
        return -1;
    }

    atexit_functions[ atexit_count++ ] = function;

    return 0;
}



void exit( int status ) {
    uint32_t i;

    for ( i = 0; i < atexit_count; i++ ) {
        atexit_functions[ i ]();
    }

    fflush( stdout );
    syscall1( SYS_exit, status );
	for (;;);
}
