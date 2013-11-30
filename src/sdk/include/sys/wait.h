

#ifndef _SYS_WAIT_H_
#define _SYS_WAIT_H_

#include <sys/types.h>
#include <sys/resource.h>

#define WNOHANG   1
#define WUNTRACED 2

pid_t wait( int* status );
pid_t waitpid( pid_t pid, int* status, int options );
pid_t wait3( int* status, int options, struct rusage* rusage );
pid_t wait4( pid_t pid, int* status, int options, struct rusage* rusage );

#endif /* _SYS_WAIT_H_ */
