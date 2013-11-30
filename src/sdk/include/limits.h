
 

#ifndef _LIMITS_H_
#define _LIMITS_H_

#ifndef __INT_MAX__
#define __INT_MAX__ 2147483647
#endif
#ifndef __LONG_MAX__
#if __WORDSIZE == 64
#define __LONG_MAX__ 9223372036854775807L
#else
#define __LONG_MAX__ 2147483647L
#endif
#endif

#define CHAR_BIT 8

#define SCHAR_MIN     (-128)
#define SCHAR_MAX     127

#define UCHAR_MAX     255

#ifdef __CHAR_UNSIGNED__
#define CHAR_MIN     0
#define CHAR_MAX     UCHAR_MAX
#else
#define CHAR_MIN     SCHAR_MIN
#define CHAR_MAX     SCHAR_MAX
#endif

#define SHRT_MIN      (-32768)
#define SHRT_MAX      32767

#define USHRT_MAX     65535

#define INT_MIN         (-1 - INT_MAX)
#define INT_MAX         (__INT_MAX__)
#define UINT_MAX        (INT_MAX * 2U + 1U)

#define LONG_MIN        (-1L - LONG_MAX)
#define LONG_MAX        ((__LONG_MAX__) + 0L)
#define ULONG_MAX       (LONG_MAX * 2UL + 1UL)

#define LLONG_MAX 9223372036854775807LL
#define LLONG_MIN (-LLONG_MAX - 1LL)
#define ULLONG_MAX 18446744073709551615ULL

#define PATH_MAX 256
#define MB_LEN_MAX 16

#endif // _LIMITS_H_
