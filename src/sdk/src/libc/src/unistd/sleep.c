#include <unistd.h>

#include <os.h>

unsigned int sleep( unsigned int seconds ) {
    uint64_t time;

    time = seconds * 1000000;

    syscall2( SYS_sleep_thread, ( int )&time, ( int )NULL );

    return 0;
}
