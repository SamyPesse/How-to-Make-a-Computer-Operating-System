#include <unistd.h>
#include <stdarg.h>
#include <errno.h>
#include <alloca.h>

int execlp( const char* file, const char* arg, ... ) {
    int i;
    int n;
    va_list ap;
    va_list bak;
    char* tmp;
    char** argv;

    va_start( ap, arg );
    __va_copy( bak, ap );

    n = 2;

    while ( ( tmp = va_arg( ap, char* ) ) != NULL ) {
        ++n;
    }

    va_end( ap );

    argv = ( char** )alloca( n * sizeof( char* ) );

    if ( argv != NULL ) {
        argv[ 0 ]= ( char* )arg;

        for ( i = 0 ; i < n; ++i ) {
            argv[ i + 1 ] = va_arg( bak, char* );
        }

        va_end( bak );

        return execvp( file, argv );
    }

    va_end( bak );

    errno = ENOMEM;

    return -1;
}
