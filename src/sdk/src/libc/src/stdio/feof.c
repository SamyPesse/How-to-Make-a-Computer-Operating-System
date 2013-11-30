
 

#include <stdio.h>

int feof( FILE* stream ) {
    if ( stream->has_ungotten ) {
        return 0;
    }

    return ( stream->flags & __FILE_EOF );
}
