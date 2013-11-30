#include <unistd.h>
#include <os.h>

uid_t getuid( void ) {
	return syscall0( SYS_getuid );
}
