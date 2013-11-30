#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/stat.h>

static char ttyname_buffer[ 128 ];

int ttyname_r( int fd, char* buf, size_t buflen ) {
    int dir;
    int error;
    int found;

    struct stat st;
    struct dirent entry;

    error = fstat( fd, &st );

    if ( error < 0 ) {
        return -1;
    }

    dir = open( "/device/terminal", O_RDONLY );

    if ( dir < 0 ) {
        return -1;
    }

    found = 0;

    while ( getdents( dir, &entry, sizeof( struct dirent ) ) == 1 ) {
        if ( entry.d_ino == st.st_ino ) {
            snprintf( buf, buflen, "/device/terminal/%s", entry.d_name );
            found = 1;
            break;
        }
    }

    close( dir );

    if ( !found ) {
        return -1;
    }

    return 0;
}

char* ttyname( int fd ) {
    int error;

    error = ttyname_r( fd, ttyname_buffer, sizeof( ttyname_buffer ) );

    if ( error < 0 ) {
        return NULL;
    }

    return ttyname_buffer;
}
