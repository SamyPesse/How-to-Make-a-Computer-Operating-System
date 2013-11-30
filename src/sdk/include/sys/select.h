

#ifndef _SYS_SELECT_H_
#define _SYS_SELECT_H_

#include <sys/time.h>
#include <sys/types.h>

#define FD_ZERO(set) \
    memset( (set)->fds, 0, 1024 / 32 );

#define FD_CLR(fd,set) \
    (set)->fds[fd/32] &= ~(1<<(fd%32));

#define FD_SET(fd,set) \
    (set)->fds[fd/32] |= (1<<(fd%32));

#define FD_ISSET(fd,set) \
    ((set)->fds[fd/32] & (1<<(fd%32)))

typedef struct fd_set {
    uint32_t fds[ 1024 / 32 ];
} fd_set;

int select( int fds, fd_set* readfds, fd_set* writefds, fd_set* exceptfds, struct timeval* timeout );

#endif // _SYS_SELECT_H_
