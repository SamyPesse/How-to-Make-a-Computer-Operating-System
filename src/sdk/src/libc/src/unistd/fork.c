#include <unistd.h>

#include <os.h>

pid_t fork( void ) {
    return syscall0( SYS_fork );
}
