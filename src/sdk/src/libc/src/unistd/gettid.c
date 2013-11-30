
 

#include <errno.h>
#include <unistd.h>

#include <os.h>

pid_t gettid( void ) {
    return syscall0( SYS_gettid );
}
