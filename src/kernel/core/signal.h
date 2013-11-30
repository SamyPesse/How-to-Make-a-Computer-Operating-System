
#ifndef SIGNAL_H
#define SIGNAL_H


#include <runtime/types.h>
#include <process.h>

	#define SIGHUP    1       /* Hangup (POSIX).  */
	#define SIGINT    2       /* Interrupt (ANSI).  */
	#define SIGQUIT   3       /* Quit (POSIX).  */
	#define SIGILL    4       /* Illegal instruction (ANSI).  */
	#define SIGTRAP   5       /* Trace trap (POSIX).  */
	#define SIGABRT   6       /* Abort (ANSI).  */
	#define SIGIOT    6       /* IOT trap (4.2 BSD).  */
	#define SIGBUS    7       /* BUS error (4.2 BSD).  */
	#define SIGFPE    8       /* Floating-point exception (ANSI).  */
	#define SIGKILL   9       /* Kill, unblockable (POSIX).  */
	#define SIGUSR1   10      /* User-defined signal 1 (POSIX).  */
	#define SIGSEGV   11      /* Segmentation violation (ANSI).  */
	#define SIGUSR2   12      /* User-defined signal 2 (POSIX).  */
	#define SIGPIPE   13      /* Broken pipe (POSIX).  */
	#define SIGALRM   14      /* Alarm clock (POSIX).  */
	#define SIGTERM   15      /* Termination (ANSI).  */
	#define SIGSTKFLT 16      /* Stack fault.  */
	#define SIGCLD    SIGCHLD /* Same as SIGCHLD (System V).  */
	#define SIGCHLD   17      /* Child status has changed (POSIX).  */
	#define SIGCONT   18      /* Continue (POSIX).  */
	#define SIGSTOP   19      /* Stop, unblockable (POSIX).  */
	#define SIGTSTP   20      /* Keyboard stop (POSIX).  */
	#define SIGTTIN   21      /* Background read from tty (POSIX).  */
	#define SIGTTOU   22      /* Background write to tty (POSIX).  */
	#define SIGURG    23      /* Urgent condition on socket (4.2 BSD).  */
	#define SIGXCPU   24      /* CPU limit exceeded (4.2 BSD).  */
	#define SIGXFSZ   25      /* File size limit exceeded (4.2 BSD).  */
	#define SIGVTALRM 26      /* Virtual alarm clock (4.2 BSD).  */
	#define SIGPROF   27      /* Profiling alarm clock (4.2 BSD).  */
	#define SIGWINCH  28      /* Window size change (4.3 BSD, Sun).  */
	#define SIGPOLL   SIGIO   /* Pollable event occurred (System V).  */
	#define SIGIO     29      /* I/O now possible (4.2 BSD).  */
	#define SIGPWR    30      /* Power failure restart (System V).  */
	#define SIGSYS    31      /* Bad system call.  */

	#define SIGEVENT	SIGPOLL
	#define SIGIPC		SIGUSR1
	
	
	
	#define SIG_DFL		0	/* default signal handling */
	#define SIG_IGN		1	/* ignore signal */

	#define set_signal(mask, sig)	*(mask) |= ((u32) 1 << (sig - 1))
	#define clear_signal(mask, sig)	*(mask) &= ~((u32) 1 << (sig - 1))
	#define is_signal(mask, sig)	(mask & ((u32) 1 << (sig - 1)))




#endif
