
 

#include <stdlib.h>
#include <string.h>

extern char** environ;

char* getenv( const char* name ) {
	return NULL;
	
    int i;
    size_t length;
    size_t name_length;

    name_length = strlen( name );

    for ( i = 0; environ[ i ] != NULL; i++ ) {
        length = strlen( environ[ i ] );

        if ( length < ( name_length + 1 ) ) {
            continue;
        }

        if ( ( strncmp( environ[ i ], name, name_length ) == 0 ) &&
             ( environ[ i ][ name_length ] == '=' ) ) {
            return &environ[ i ][ name_length + 1 ];
        }
    }

    return NULL;
}
