
 

#ifndef _DIRENT_H_
#define _DIRENT_H_

#include <unistd.h>


typedef struct DIR {
    int fd;
    struct dirent entry;
} DIR;

DIR* opendir( const char* name );
int closedir( DIR* dir );

struct dirent* readdir( DIR* dir );
int readdir_r( DIR* dir, struct dirent* entry, struct dirent** result );

void rewinddir( DIR* dir );

#endif /* _DIRENT_H_ */
