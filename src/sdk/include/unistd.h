
 

#ifndef _UNISTD_H_
#define _UNISTD_H_

#include <string.h>
#include <sys/types.h>

#define STDIN_FILENO  0
#define STDOUT_FILENO 1
#define STDERR_FILENO 2

#define F_OK 0x00
#define R_OK 0x01
#define W_OK 0x02
#define X_OK 0x04

#define NAME_MAX 255

#define _D_EXACT_NAMLEN(d) (strlen((d)->d_name))
#define _D_ALLOC_NAMLEN(d) (NAME_MAX+1)

enum {
    _PC_LINK_MAX,
#define _PC_LINK_MAX                    _PC_LINK_MAX
    _PC_MAX_CANON,
#define _PC_MAX_CANON                   _PC_MAX_CANON
    _PC_MAX_INPUT,
#define _PC_MAX_INPUT                   _PC_MAX_INPUT
    _PC_NAME_MAX,
#define _PC_NAME_MAX                    _PC_NAME_MAX
    _PC_PATH_MAX,
#define _PC_PATH_MAX                    _PC_PATH_MAX
    _PC_PIPE_BUF,
#define _PC_PIPE_BUF                    _PC_PIPE_BUF
    _PC_CHOWN_RESTRICTED,
#define _PC_CHOWN_RESTRICTED            _PC_CHOWN_RESTRICTED
    _PC_NO_TRUNC,
#define _PC_NO_TRUNC                    _PC_NO_TRUNC
    _PC_VDISABLE,
#define _PC_VDISABLE                    _PC_VDISABLE
    _PC_SYNC_IO,
#define _PC_SYNC_IO                     _PC_SYNC_IO
    _PC_ASYNC_IO,
#define _PC_ASYNC_IO                    _PC_ASYNC_IO
    _PC_PRIO_IO,
#define _PC_PRIO_IO                     _PC_PRIO_IO
    _PC_SOCK_MAXBUF,
#define _PC_SOCK_MAXBUF                 _PC_SOCK_MAXBUF
    _PC_FILESIZEBITS,
#define _PC_FILESIZEBITS                _PC_FILESIZEBITS
    _PC_REC_INCR_XFER_SIZE,
#define _PC_REC_INCR_XFER_SIZE          _PC_REC_INCR_XFER_SIZE
    _PC_REC_MAX_XFER_SIZE,
#define _PC_REC_MAX_XFER_SIZE           _PC_REC_MAX_XFER_SIZE
    _PC_REC_MIN_XFER_SIZE,
#define _PC_REC_MIN_XFER_SIZE           _PC_REC_MIN_XFER_SIZE
    _PC_REC_XFER_ALIGN,
#define _PC_REC_XFER_ALIGN              _PC_REC_XFER_ALIGN
    _PC_ALLOC_SIZE_MIN,
#define _PC_ALLOC_SIZE_MIN              _PC_ALLOC_SIZE_MIN
    _PC_SYMLINK_MAX,
#define _PC_SYMLINK_MAX                 _PC_SYMLINK_MAX
    _PC_2_SYMLINKS
#define _PC_2_SYMLINKS                  _PC_2_SYMLINKS
};

struct dirent {
    ino_t d_ino;
    char d_name[ NAME_MAX + 1 ];
};

void _exit( int status );

pid_t fork( void );

int execv( const char* file, char* const argv[] );
int execve( const char* filename, char* const argv[], char* const envp[] );
int execvp( const char* filename, char* const argv[] );
int execlp( const char* file, const char* arg, ... );

void* sbrk( int increment );

int open( const char* filename, int flags, ... );
int close( int fd );
int dup( int old_fd );
int dup2( int old_fd, int new_fd );

ssize_t read( int fd, void* buf, size_t count );
ssize_t write( int fd, const void* buf, size_t count );
ssize_t pread( int fd, void* buf, size_t count, off_t offset );
ssize_t pwrite( int fd, const void* buf, size_t count, off_t offset );
off_t lseek( int fd, off_t offset, int whence );

int pipe( int pipefd[2] );
int isatty( int fd );
int chdir( const char* path );
int fchdir( int fd );
int getdents( int fd, struct dirent* entry, unsigned int count );
int ftruncate( int fd, off_t length );

int link( const char* oldpath, const char* newpath );
int access( const char* pathname, int mode );
int unlink( const char* pathname );
ssize_t readlink( const char* path, char* buf, size_t bufsiz );
int rmdir( const char* pathname );
int chown( const char* path, uid_t owner, gid_t group );
char* getcwd( char* buf, size_t size );
int symlink( const char* oldpath, const char* newpath );
char* ttyname( int fd );
int ttyname_r( int fd, char* buf, size_t buflen );

pid_t getpid( void );
pid_t getppid( void );
pid_t gettid( void );
int getpagesize( void );
int getdtablesize( void );

int gethostname( char* name, size_t len );

unsigned int sleep( unsigned int seconds );
unsigned int alarm( unsigned int seconds );

long fpathconf( int fd, int name );

uid_t getuid( void );
uid_t geteuid( void );
int setuid( uid_t uid );
int setreuid( uid_t ruid, uid_t euid );

gid_t getgid( void );
gid_t getegid( void );
int setgid( gid_t gid );
int setregid( gid_t rgid, gid_t egid );

pid_t tcgetpgrp( int fd );
int tcsetpgrp( int fd, pid_t pgrp );

pid_t getpgid( pid_t pid );
int setpgid( pid_t pid, pid_t pgid );

pid_t getpgrp( void );
int setpgrp( void );

#endif /* _UNISTD_H_ */
