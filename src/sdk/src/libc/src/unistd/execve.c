
 

#include <errno.h>
#include <unistd.h>

#include <os.h>

int execve( const char* filename, char* const argv[], char* const envp[] ) {
    int error;

    error = syscall3( SYS_execve, ( int )filename, ( int )argv, ( int )envp );

    if ( error < 0 ) {
        errno = -error;
        return -1;
    }

    return error;
}
