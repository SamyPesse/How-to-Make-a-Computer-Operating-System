#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <stdio.h>

extern char** environ;

int execvp( const char* filename, char* const argv[] ) {
    char* path;
    char* separator;
    char tmp_path[ 128 ];
    char tmp_exec[ 128 ];

    execve( filename, argv, environ );

    path = getenv( "PATH" );

    if ( path == NULL ) {
        return -1;
    }

    do {
        separator = strchr( path, ':' );

        if ( separator == NULL ) {
            memcpy( tmp_path, path, strlen( path ) + 1 );
        } else {
            size_t length = ( separator - path );

            memcpy( tmp_path, path, length );
            tmp_path[ length ] = 0;
        }

        snprintf( tmp_exec, sizeof( tmp_exec ), "%s/%s", tmp_path, filename );
        execve( tmp_exec, argv, environ );

        path = separator + 1;
    } while ( separator != NULL );

    return -1;
}
