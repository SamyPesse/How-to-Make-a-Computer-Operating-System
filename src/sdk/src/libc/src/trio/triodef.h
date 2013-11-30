

#ifndef TRIO_TRIODEF_H
#define TRIO_TRIODEF_H

/*************************************************************************
 * Compiler support detection
 */

#if defined(__GNUC__)
# define TRIO_COMPILER_GCC
#endif

#if defined(__SUNPRO_CC)
# define TRIO_COMPILER_SUNPRO __SUNPRO_CC
#else
# if defined(__SUNPRO_C)
#  define TRIO_COMPILER_SUNPRO __SUNPRO_C
# endif
#endif

#if defined(__xlC__) || defined(__IBMC__) || defined(__IBMCPP__)
# define TRIO_COMPILER_XLC
#else
# if defined(_AIX) && !defined(__GNUC__)
#  define TRIO_COMPILER_XLC /* Workaround for old xlc */
# endif
#endif

#if defined(__DECC) || defined(__DECCXX)
# define TRIO_COMPILER_DECC
#else
# if defined(__osf__) && defined(__LANGUAGE_C__) && !defined(__GNUC__)
#  define TRIO_COMPILER_DECC /* Workaround for old DEC C compilers */
# endif
#endif

#if defined(__HP_aCC) || defined(__HP_cc)
# define TRIO_COMPILER_HP
#endif

#if defined(sgi) || defined(__sgi)
# define TRIO_COMPILER_MIPSPRO
#endif

#if defined(_MSC_VER)
# define TRIO_COMPILER_MSVC
#endif

#if defined(__BORLANDC__)
# define TRIO_COMPILER_BCB
#endif

/*************************************************************************
 * Platform support detection
 */

#if defined(VMS) || defined(__VMS)
# define TRIO_PLATFORM_VMS
#endif

#if defined(unix) || defined(__unix) || defined(__unix__)
# define TRIO_PLATFORM_UNIX
#endif

#if defined(TRIO_COMPILER_XLC) || defined(_AIX)
# define TRIO_PLATFORM_UNIX
#endif

#if defined(TRIO_COMPILER_DECC) || defined(__osf___)
# if !defined(TRIO_PLATFORM_VMS)
#  define TRIO_PLATFORM_UNIX
# endif
#endif

#if defined(__NetBSD__)
# define TRIO_PLATFORM_UNIX
#endif

#if defined(__Lynx__)
# define TRIO_PLATFORM_UNIX
# define TRIO_PLATFORM_LYNX
#endif

#if defined(__APPLE__) && defined(__MACH__)
# define TRIO_PLATFORM_UNIX
#endif

#if defined(__QNX__)
# define TRIO_PLATFORM_UNIX
# define TRIO_PLATFORM_QNX
#endif

#if defined(__CYGWIN__)
# define TRIO_PLATFORM_UNIX
#endif

#if defined(AMIGA) && defined(TRIO_COMPILER_GCC)
# define TRIO_PLATFORM_UNIX
#endif

#if defined(TRIO_COMPILER_MSVC) || defined(WIN32) || defined(_WIN32)
# define TRIO_PLATFORM_WIN32
#endif

#if defined(_WIN32_WCE)
# define TRIO_PLATFORM_WINCE
#endif

#if defined(mpeix) || defined(__mpexl)
# define TRIO_PLATFORM_MPEIX
#endif

#if defined(_AIX)
# define TRIO_PLATFORM_AIX
#endif

#if defined(__hpux)
# define TRIO_PLATFORM_HPUX
#endif

#if defined(sun) || defined(__sun__)
# if defined(__SVR4) || defined(__svr4__)
#  define TRIO_PLATFORM_SOLARIS
# else
#  define TRIO_PLATFORM_SUNOS
# endif
#endif

/*************************************************************************
 * Standards support detection
 */

#if defined(__STDC__) \
 || defined(_MSC_EXTENSIONS) \
 || defined(TRIO_COMPILER_BORLAND)
# define PREDEF_STANDARD_C89
#endif
#if defined(__STDC_VERSION__)
# define PREDEF_STANDARD_C90
#endif
#if (__STDC_VERSION__ - 0 >= 199409L)
# define PREDEF_STANDARD_C94
#endif
#if (__STDC_VERSION__ - 0 >= 199901L)
# define PREDEF_STANDARD_C99
#endif
#if defined(TRIO_COMPILER_SUNPRO) && (TRIO_COMPILER_SUNPRO >= 0x420)
# if !defined(PREDEF_STANDARD_C94)
#  define PREDEF_STANDARD_C94
# endif
#endif

#if defined(__cplusplus)
# define PREDEF_STANDARD_CXX
#endif
#if __cplusplus - 0 >= 199711L
# define PREDEF_STANDARD_CXX89
#endif

#if defined(TRIO_PLATFORM_UNIX)
# include <unistd.h>
#endif

#if defined(_POSIX_VERSION)
# define PREDEF_STANDARD_POSIX _POSIX_VERSION
# if (_POSIX_VERSION >= 199506L)
#  define PREDEF_STANDARD_POSIX_1996
# endif
#endif

#if (_XOPEN_VERSION - 0 >= 3) || defined(_XOPEN_XPG3)
# define PREDEF_STANDARD_XPG3
#endif
#if (_XOPEN_VERSION - 0 >= 4) || defined(_XOPEN_XPG4)
# define PREDEF_STANDARD_XPG4
#endif
#if (_XOPEN_VERSION - 0 > 4) \
 || (defined(_XOPEN_UNIX) && (_XOPEN_VERSION - 0 == 4))
# define PREDEF_STANDARD_UNIX95
#endif
#if (_XOPEN_VERSION - 0 >= 500)
# define PREDEF_STANDARD_UNIX98
#endif
#if (_XOPEN_VERSION - 0 >= 600)
# define PREDEF_STANDARD_UNIX03
#endif

/*************************************************************************
 * Generic defines
 */

#if !defined(TRIO_PUBLIC)
# define TRIO_PUBLIC
#endif
#if !defined(TRIO_PRIVATE)
# define TRIO_PRIVATE static
#endif

#if !(defined(PREDEF_STANDARD_C89) || defined(PREDEF_STANDARD_CXX))
# define TRIO_COMPILER_ANCIENT
#endif

#if defined(TRIO_COMPILER_ANCIENT)
# define TRIO_CONST
# define TRIO_VOLATILE
# define TRIO_SIGNED
typedef double trio_long_double_t;
typedef char * trio_pointer_t;
# define TRIO_SUFFIX_LONG(x) x
# define TRIO_PROTO(x) ()
# define TRIO_NOARGS
# define TRIO_ARGS1(list,a1) list a1;
# define TRIO_ARGS2(list,a1,a2) list a1; a2;
# define TRIO_ARGS3(list,a1,a2,a3) list a1; a2; a3;
# define TRIO_ARGS4(list,a1,a2,a3,a4) list a1; a2; a3; a4;
# define TRIO_ARGS5(list,a1,a2,a3,a4,a5) list a1; a2; a3; a4; a5;
# define TRIO_ARGS6(list,a1,a2,a3,a4,a5,a6) list a1; a2; a3; a4; a5; a6;
# define TRIO_VARGS2(list,a1,a2) list a1; a2
# define TRIO_VARGS3(list,a1,a2,a3) list a1; a2; a3
# define TRIO_VARGS4(list,a1,a2,a3,a4) list a1; a2; a3; a4
# define TRIO_VARGS5(list,a1,a2,a3,a4,a5) list a1; a2; a3; a4; a5
# define TRIO_VA_DECL va_dcl
# define TRIO_VA_START(x,y) va_start(x)
# define TRIO_VA_END(x) va_end(x)
#else /* ANSI C */
# define TRIO_CONST const
# define TRIO_VOLATILE volatile
# define TRIO_SIGNED signed
typedef long double trio_long_double_t;
typedef void * trio_pointer_t;
# define TRIO_SUFFIX_LONG(x) x ## L
# define TRIO_PROTO(x) x
# define TRIO_NOARGS void
# define TRIO_ARGS1(list,a1) (a1)
# define TRIO_ARGS2(list,a1,a2) (a1,a2)
# define TRIO_ARGS3(list,a1,a2,a3) (a1,a2,a3)
# define TRIO_ARGS4(list,a1,a2,a3,a4) (a1,a2,a3,a4)
# define TRIO_ARGS5(list,a1,a2,a3,a4,a5) (a1,a2,a3,a4,a5)
# define TRIO_ARGS6(list,a1,a2,a3,a4,a5,a6) (a1,a2,a3,a4,a5,a6)
# define TRIO_VARGS2 TRIO_ARGS2
# define TRIO_VARGS3 TRIO_ARGS3
# define TRIO_VARGS4 TRIO_ARGS4
# define TRIO_VARGS5 TRIO_ARGS5
# define TRIO_VA_DECL ...
# define TRIO_VA_START(x,y) va_start(x,y)
# define TRIO_VA_END(x) va_end(x)
#endif

#if defined(PREDEF_STANDARD_C99) || defined(PREDEF_STANDARD_CXX)
# define TRIO_INLINE inline
#else
# if defined(TRIO_COMPILER_GCC)
#  define TRIO_INLINE __inline__
# endif
# if defined(TRIO_COMPILER_MSVC)
#  define TRIO_INLINE _inline
# endif
# if defined(TRIO_COMPILER_BCB)
#  define TRIO_INLINE __inline
# endif
#endif
#if !defined(TRIO_INLINE)
# define TRIO_INLINE
#endif

/*************************************************************************
 * Workarounds
 */

#if defined(TRIO_PLATFORM_VMS)
/*
 * Computations done with constants at compile time can trigger these
 * even when compiling with IEEE enabled.
 */
# pragma message disable (UNDERFLOW, FLOATOVERFL)

# if (__CRTL_VER < 80210001)
/*
 * Although the compiler supports C99 language constructs, the C
 * run-time library does not contain all C99 functions.
 */
#  if defined(PREDEF_STANDARD_C99)
#   undef PREDEF_STANDARD_C99
#  endif
# endif
#endif

/*
 * Not all preprocessors supports the LL token.
 */
#if defined(TRIO_COMPILER_MSVC) || defined(TRIO_COMPILER_BCB)
#else
# define TRIO_COMPILER_SUPPORTS_LL
#endif

#endif /* TRIO_TRIODEF_H */
