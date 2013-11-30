
 

#include <string.h>

static char* signal_names[] = {
    "Hangup",
    "Interrupt",
    "Quit",
    "Illegal instruction",
    "Trace/breakpoint trap",
    "Aborted",
    "Aborted",
    "Bus error",
    "Floating point exception",
    "Killed",
    "User defined signal 1",
    "Segmentation fault",
    "User defined signal 2",
    "Broken pipe",
    "Alarm clock",
    "Terminated",
    "Stack fault",
    "Child exited",
    "Continued",
    "Stopped (signal)",
    "Stopped",
    "Stopped (tty input)",
    "Stopped (tty output)",
    "Urgent I/O condition",
    "CPU time limit exceeded",
    "File size limit exceeded",
    "Virtual timer expired",
    "Profiling timer expired",
    "Window changed",
    "I/O possible",
    "Power failure",
    "Bad system call"
};

char* strsignal( int signum ) {
    if ( signum <= 0 ) {
        return NULL;
    }

    signum--;

    if ( signum >= ( sizeof( signal_names ) / sizeof( signal_names[ 0 ] ) ) ) {
        return NULL;
    }

    return signal_names[ signum ];
}
