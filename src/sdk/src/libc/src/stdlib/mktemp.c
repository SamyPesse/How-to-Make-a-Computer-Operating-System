#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <stdlib.h>

char* mktemp( char* template ) {
    int fd;

    fd = mkstemp( template );

    if ( fd < 0 ) {
        return NULL;
    }

    close( fd );

    unlink( template );

    return template;
}
