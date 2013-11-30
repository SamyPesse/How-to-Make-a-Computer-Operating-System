
 

#include <stdio.h>

int fileno( FILE* stream ) {
    return stream->fd;
}
