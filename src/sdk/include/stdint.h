
 

#ifndef _STDINT_H_
#define _STDINT_H_

typedef signed char int8_t;
typedef signed short int16_t;
typedef signed int int32_t;
typedef signed long long int64_t;
typedef unsigned char uint8_t;
typedef unsigned short uint16_t;
typedef unsigned int uint32_t;
typedef unsigned long long uint64_t;

typedef signed long intptr_t;
typedef unsigned long uintptr_t;

#if __WORDSIZE == 64
typedef signed long int intmax_t;
typedef unsigned long int uintmax_t;
#else
typedef signed long long int intmax_t;
typedef unsigned long long int uintmax_t;
#endif /* __WORDSIZE == 64 */

/* The ISO C99 standard specifies that in C++ implementations these
   macros should only be defined if explicitly requested.  */

#if !defined __cplusplus || defined __STDC_LIMIT_MACROS

#if __WORDSIZE == 64
#define __INT64_C(c)  c ## L
#define __UINT64_C(c) c ## UL
#else
#define __INT64_C(c)  c ## LL
#define __UINT64_C(c) c ## ULL
#endif

/* Limits of integral types.  */

/* Minimum of signed integral types.  */
# define INT8_MIN               (-128)
# define INT16_MIN              (-32767-1)
# define INT32_MIN              (-2147483647-1)
# define INT64_MIN              (-__INT64_C(9223372036854775807)-1)

/* Maximum of signed integral types.  */
# define INT8_MAX               (127)
# define INT16_MAX              (32767)
# define INT32_MAX              (2147483647)
# define INT64_MAX              (__INT64_C(9223372036854775807))

/* Maximum of unsigned integral types.  */
# define UINT8_MAX              (255)
# define UINT16_MAX             (65535)
# define UINT32_MAX             (4294967295U)
# define UINT64_MAX             (__UINT64_C(18446744073709551615))

#endif

#endif /* _STDINT_H_ */
