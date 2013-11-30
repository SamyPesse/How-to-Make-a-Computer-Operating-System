
 

#include <stdio.h>

static char __stdin_buffer[ _IO_BUFSIZE ];
static char __stdout_buffer[ _IO_BUFSIZE ];
static char __stderr_buffer[ _IO_BUFSIZE ];

static FILE _stdin = {
    .fd = 0,
    .flags = __FILE_CAN_READ | __FILE_DONTFREEBUF | __FILE_BUFLINEWISE | __FILE_BUFINPUT,
    .buffer = __stdin_buffer,
    .buffer_pos = 0,
    .buffer_size = _IO_BUFSIZE,
    .buffer_data_size = 0,
    .has_ungotten = 0,
    .unget_buffer = -1
};

static FILE _stdout = {
    .fd = 1,
    .flags = __FILE_CAN_WRITE | __FILE_BUFLINEWISE | __FILE_DONTFREEBUF,
    .buffer = __stdout_buffer,
    .buffer_pos = 0,
    .buffer_size = _IO_BUFSIZE,
    .buffer_data_size = 0,
    .has_ungotten = 0,
    .unget_buffer = -1
};

static FILE _stderr = {
    .fd = 2,
    .flags = __FILE_CAN_WRITE | __FILE_DONTFREEBUF | __FILE_NOBUF,
    .buffer = __stderr_buffer,
    .buffer_pos = 0,
    .buffer_size = _IO_BUFSIZE,
    .buffer_data_size = 0,
    .has_ungotten = 0,
    .unget_buffer = -1
};

FILE* stdin = &_stdin;
FILE* stdout = &_stdout;
FILE* stderr = &_stderr;
