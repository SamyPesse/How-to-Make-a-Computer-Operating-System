

#ifndef _SYS_TYPES_H_
#define _SYS_TYPES_H_

#include <stdint.h>

#define __need_size_t
#include <stddef.h>

#ifndef NULL
#ifdef __cplusplus
#define NULL 0
#else
#define NULL ((void*)0)
#endif /* __cplusplus */
#endif /* NULL */

#define INFINITE_TIMEOUT 18446744073709551615ULL

typedef unsigned char u_char;

typedef int ssize_t;
typedef int pid_t;
typedef int64_t ino_t;
typedef int64_t off_t;
typedef int dev_t;
typedef int mode_t;
typedef int nlink_t;
typedef int uid_t;
typedef int gid_t;
typedef int blksize_t;
typedef int64_t blkcnt_t;

#endif /* _SYS_TYPES_H_ */
