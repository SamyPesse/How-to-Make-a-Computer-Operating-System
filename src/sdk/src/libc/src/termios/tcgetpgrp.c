#include <unistd.h>

pid_t tcgetpgrp( int fd ) {
    /* NOTE: This is a temp. hack to get bash working :) */

    return getpid();
}
