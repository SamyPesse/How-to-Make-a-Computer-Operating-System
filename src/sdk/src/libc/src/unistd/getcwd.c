
 

#include <stdlib.h>
#include <unistd.h>
#include <dirent.h>
#include <errno.h>
#include <string.h>
#include <limits.h>
#include <sys/stat.h>
#include <sys/param.h>

char* getcwd( char* buf, size_t size ) {
    static const char dots[] = "../../../../../../../../../../../../../../../../../../../../../../../\
        ../../../../../../../../../../../../../../../../../../../../../../../../../../\
        ../../../../../../../../../../../../../../../../../../../../../../../../../..";
    const char* dotp = &dots[ sizeof( dots ) ];
    const char* dotlist = dots;
    size_t dotsize = sizeof( dots ) - 1;
    dev_t rootdev, thisdev;
    ino_t rootino, thisino;
    char* path;
    register char* pathp;
    struct stat st;
    size_t allocated = size;

    if ( size == 0 ) {
        if ( buf != NULL ) {
            return NULL;
        }

        allocated = PATH_MAX + 1;
    }

    if ( buf != NULL ) {
        path = buf;
    } else {
        path = malloc( allocated );

        if ( path == NULL ) {
            return NULL;
        }
    }

    pathp = path + allocated;
    *--pathp = '\0';

    if ( stat( ".", &st ) < 0 ) {
        goto lose2;
    }

    thisdev = st.st_dev;
    thisino = st.st_ino;

    if ( stat( "/", &st ) < 0 ) {
        goto lose2;
    }

    rootdev = st.st_dev;
    rootino = st.st_ino;

    while ( !( thisdev == rootdev && thisino == rootino ) ) {
        register DIR *dirstream;
        struct dirent* d;
        dev_t dotdev;
        ino_t dotino;
        char mount_point;

        /* Look at the parent directory.  */

        if ( dotp == dotlist ) {
            /* My, what a deep directory tree you have, Grandma.  */

            char* new;

            if ( dotlist == dots ) {
                new = malloc( dotsize * 2 + 1 );

                if ( new == NULL ) {
                    goto lose;
                }

#ifdef HAVE_MEMPCPY
                dotp = mempcpy( new, dots, dotsize );
#else
                memcpy( new, dots, dotsize );
                dotp = &new[ dotsize ];
#endif
            } else {
                new = realloc( ( void* )dotlist, dotsize * 2 + 1 );

                if ( new == NULL ) {
                    goto lose;
                }

                dotp = &new[ dotsize ];
            }
#ifdef HAVE_MEMPCPY
            *( ( char* )mempcpy( ( char* )dotp, new, dotsize ) ) = '\0';
            dotsize *= 2;
#else
            memcpy( ( char* )dotp, new, dotsize );
            dotsize *= 2;
            new[ dotsize ] = '\0';
#endif
            dotlist = new;
        }

        dotp -= 3;

        /* Figure out if this directory is a mount point. */

        if ( stat( dotp, &st ) < 0 ) {
            goto lose;
        }

        dotdev = st.st_dev;
        dotino = st.st_ino;
        mount_point = dotdev != thisdev;

        /* Search for the last directory. */

        dirstream = opendir( dotp );

        if ( dirstream == NULL ) {
            goto lose;
        }

        while ( ( d = readdir( dirstream ) ) != NULL ) {
            if ( d->d_name[ 0 ] == '.' &&
                 ( d->d_name[ 1 ] == '\0' || (d->d_name[ 1 ] == '.' && d->d_name[ 2 ] == '\0' ) ) ) {
                continue;
            }

            if ( mount_point || ( ino_t )d->d_ino == thisino ) {
                char name[ dotlist + dotsize - dotp + 1 + _D_ALLOC_NAMLEN( d ) ];

#ifdef HAVE_MEMPCPY
                char *tmp = mempcpy( name, dotp, dotlist + dotsize - dotp );
                *tmp++ = '/';
                strcpy( tmp, d->d_name );
#else
                memcpy( name, dotp, dotlist + dotsize - dotp );
                name[ dotlist + dotsize - dotp ] = '/';
                strcpy( &name[ dotlist + dotsize - dotp + 1 ], d->d_name );
#endif

                /* We don't fail here if we cannot stat() a directory entry.
                   This can happen when (network) filesystems fail.  If this
                   entry is in fact the one we are looking for we will find
                   out soon as we reach the end of the directory without
                   having found anything.  */

                if ( stat( name, &st ) >= 0 &&
                     st.st_dev == thisdev && st.st_ino == thisino ) {
                    break;
                }
            }
        }

        if ( d == NULL ) {
            ( void )closedir( dirstream );

            goto lose;
        } else {
            size_t namlen = _D_EXACT_NAMLEN( d );

            if ( ( size_t )( pathp - path ) <= namlen ) {
                if (size != 0) {
                    ( void )closedir( dirstream );
                    goto lose;
                } else {
                    char* tmp;
                    size_t oldsize = allocated;

                    allocated = 2 * MAX( allocated, namlen );
                    tmp = realloc( path, allocated );

                    if ( tmp == NULL ) {
                        ( void )closedir( dirstream );
                        goto lose;
                    }

                    /* Move current contents up to the end of the buffer.
                       This is guaranteed to be non-overlapping.  */

                    pathp = memcpy(
                        tmp + allocated - ( path + oldsize - pathp ),
                        tmp + ( pathp - path ),
                        path + oldsize - pathp
                    );

                    path = tmp;
                }
            }

            pathp -= namlen;
            ( void )memcpy( pathp, d->d_name, namlen );
            *--pathp = '/';
            ( void )closedir( dirstream );
        }

        thisdev = dotdev;
        thisino = dotino;
    }

    if ( pathp == &path[ allocated - 1 ] ) {
        *--pathp = '/';
    }

    if ( dotlist != dots ) {
        free( ( void* )dotlist );
    }

    memmove( path, pathp, path + allocated - pathp );

    return path;

lose:
    if ( dotlist != dots ) {
        free( ( void* )dotlist );
    }

lose2:
    if ( buf == NULL ) {
        free( path );
    }

    return NULL;
}
