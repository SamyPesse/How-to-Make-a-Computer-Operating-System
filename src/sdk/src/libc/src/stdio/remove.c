
 

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>

int remove( const char* path ) {
  struct stat st;

  if ( stat( path, &st) != 0 ) {
    return -1;
  }

  if ( S_ISDIR( st.st_mode ) ) {
    return rmdir( path );
  } else {
    return unlink( path );
  }
}
