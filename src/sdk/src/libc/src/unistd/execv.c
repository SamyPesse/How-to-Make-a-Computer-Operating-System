#include <unistd.h>

extern char** environ;

int execv( const char* file, char* const argv[] ) {
    return execve( file, argv, environ );
}
