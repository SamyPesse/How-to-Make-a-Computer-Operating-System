
 

#ifndef _SIGNAL_H_
#define _SIGNAL_H_

#include <time.h>
#include <sys/types.h>

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

#define _NSIG     65      /* Biggest signal number + 1 (including real-time signals). */

#define SIG_ERR ((sighandler_t)-1) /* Error return.  */
#define SIG_DFL ((sighandler_t)0) /* Default action.  */
#define SIG_IGN ((sighandler_t)1) /* Ignore signal.  */

#define SIG_BLOCK   0 /* Block signals.  */
#define SIG_UNBLOCK 1 /* Unblock signals.  */
#define SIG_SETMASK 2 /* Set the set of blocked signals.  */

#define SA_NOCLDSTOP 1 /* Don't send SIGCHLD when children stop.  */
#define SA_NOCLDWAIT 2 /* Don't create zombie on child death.  */
#define SA_SIGINFO   4 /* Invoke signal-catching function with three arguments instead of one.  */
#define SA_ONSTACK   0x08000000 /* Use signal stack by using `sa_restorer'. */
#define SA_STACK     SA_ONSTACK
#define SA_RESTART   0x10000000 /* Restart syscall on signal return.  */
#define SA_NODEFER   0x40000000 /* Don't automatically block the signal when its handler is being executed.  */
#define SA_NOMASK    SA_NODEFER
#define SA_RESETHAND 0x80000000 /* Reset to SIG_DFL on entry to handler.  */
#define SA_ONESHOT   SA_RESETHAND

typedef int sig_atomic_t;
typedef uint64_t sigset_t;
typedef int sigval_t;
typedef void ( *__sighandler_t )( int );
typedef __sighandler_t sighandler_t;

typedef struct siginfo {
    int      si_signo;   /* Signal number */
    int      si_errno;   /* An errno value */
    int      si_code;    /* Signal code */
    int      si_trapno;  /* Trap number that caused
                                 hardware-generated signal
                                 (unused on most architectures) */
    pid_t    si_pid;     /* Sending process ID */
    uid_t    si_uid;     /* Real user ID of sending process */
    int      si_status;  /* Exit value or signal */
    clock_t  si_utime;   /* User time consumed */
    clock_t  si_stime;   /* System time consumed */
    sigval_t si_value;   /* Signal value */
    int      si_int;     /* POSIX.1b signal */
    void    *si_ptr;     /* POSIX.1b signal */
    int      si_overrun; /* Timer overrun count; POSIX.1b timers */
    int      si_timerid; /* Timer ID; POSIX.1b timers */
    void    *si_addr;    /* Memory location which caused fault */
    int      si_band;    /* Band event */
    int      si_fd;      /* File descriptor */
} siginfo_t;

struct sigaction {
    void ( *sa_handler )( int );
    void ( *sa_sigaction )( int, siginfo_t*, void* );
    sigset_t sa_mask;
    int sa_flags;
    void ( *sa_restorer )( void );
};

int sigemptyset( sigset_t* set );
int sigfillset( sigset_t* set );
int sigaddset( sigset_t* set, int signum );
int sigdelset( sigset_t* set, int signum );
int sigismember( const sigset_t* set, int signum );

sighandler_t signal( int signum, sighandler_t handler );
int sigaction( int signum, const struct sigaction* act, struct sigaction* oldact );
int sigprocmask( int how, const sigset_t* set, sigset_t* oldset );

int kill( pid_t pid, int signal );
int killpg( int pgrp, int signal );

int raise( int signal );

#endif /* _SIGNAL_H_ */
