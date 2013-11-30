#include <unistd.h>

#include <os.h>

pid_t getpid( void ) {
    return syscall0( SYS_getpid );
}
