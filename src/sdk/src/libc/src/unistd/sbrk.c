
 
#include <os.h>

void* sbrk( int increment ) {
    return ( void* )syscall1( SYS_sbrk, increment );
}
