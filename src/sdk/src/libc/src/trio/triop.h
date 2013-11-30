

#ifndef TRIO_TRIOP_H
#define TRIO_TRIOP_H

#include "triodef.h"

#include <stdlib.h>
#if defined(TRIO_COMPILER_ANCIENT)
# include <varargs.h>
#else
# include <stdarg.h>
#endif

#ifdef __cplusplus
extern "C" {
#endif

/*************************************************************************
 * Supported standards
 */

/*
 * TRIO_C99 (=0 or =1)
 *
 * Define this to 0 to disable C99 format specifier extensions, or
 * define to 1 to enable them.  The format specifiers that are
 * disabled by this switch are labelled with [C99] in the format
 * specifier documentation.
 */
#if !defined(TRIO_C99)
# define TRIO_C99 1
#endif

/*
 * TRIO_BSD (=0 or =1)
 *
 * Define this to 0 to disable BSD format specifier extensions, or
 * define to 1 to enable them.  The format specifiers that are
 * disabled by this switch are labelled with [BSD] in the format
 * specifier documentation.
 */
#if !defined(TRIO_BSD)
# define TRIO_BSD 1
#endif

/*
 * TRIO_GNU (=0 or =1)
 *
 * Define this to 0 to disable GNU format specifier extensions, or
 * define to 1 to enable them.  The format specifiers that are
 * disabled by this switch are labelled with [GNU] in the format
 * specifier documentation.
 */
#if !defined(TRIO_GNU)
# define TRIO_GNU 1
#endif

/*
 * TRIO_MISC (=0 or =1)
 *
 * Define this to 0 to disable miscellaneous format specifier
 * extensions, or define to 1 to enable them.  The format specifiers
 * that are disabled by this switch are labelled with [MISC] in the
 * format specifier documentation.
 */
#if !defined(TRIO_MISC)
# define TRIO_MISC 1
#endif

/*
 * TRIO_UNIX98 (=0 or =1)
 *
 * Define this to 0 to disable UNIX98 format specifier extensions,
 * or define to 1 to enable them.  The format specifiers that are
 * disabled by this switch are labelled with [UNIX98] in the format
 * specifier documentation.
 */
#if !defined(TRIO_UNIX98)
# define TRIO_UNIX98 1
#endif
  
/*
 * TRIO_MICROSOFT (=0 or =1)
 *
 * Define this to 0 to disable Microsoft Visual C format specifier
 * extensions, or define to 1 to enable them.  The format specifiers
 * that are disabled by this switch are labelled with [MSVC] in the
 * format specifier documentation.
 */
#if !defined(TRIO_MICROSOFT)
# define TRIO_MICROSOFT 1
#endif

/*
 * TRIO_EXTENSION (=0 or =1)
 *
 * Define this to 0 to disable Trio-specific extensions, or define
 * to 1 to enable them.  This has two effects: it controls whether
 * or not the Trio user-defined formating mechanism
 * (trio_register() etc) is supported, and it enables or disables
 * Trio's own format specifier extensions.  The format specifiers
 * that are disabled by this switch are labelled with [TRIO] in
 * the format specifier documentation.
 */
#if !defined(TRIO_EXTENSION)
# define TRIO_EXTENSION 1
#endif

/*
 * TRIO_DEPRECATED (=0 or =1)
 *
 * Define this to 0 to disable deprecated functionality, or define
 * to 1 to enable them.
 */
#if !defined(TRIO_DEPRECATED)
# define TRIO_DEPRECATED 1
#endif

/*************************************************************************
 * Features
 */

#if defined(TRIO_SNPRINTF_ONLY)
# define TRIO_FEATURE_SCANF 0
# define TRIO_FEATURE_FILE 0
# define TRIO_FEATURE_STDIO 0
# define TRIO_FEATURE_FD 0
# define TRIO_FEATURE_DYNAMICSTRING 0
# define TRIO_FEATURE_CLOSURE 0
# define TRIO_FEATURE_STRERR 0
# define TRIO_FEATURE_LOCALE 0
# define TRIO_EMBED_NAN 1
# define TRIO_EMBED_STRING 1
#endif
  
/*
 * TRIO_FEATURE_SCANF (=0 or =1)
 *
 * Define this to 0 to disable all the scanf() variants, or define to 1
 * to enable them.
 */
#if !defined(TRIO_FEATURE_SCANF)
# define TRIO_FEATURE_SCANF 1
#endif
  
/*
 * TRIO_FEATURE_FILE (=0 or =1)
 *
 * Define this to 0 to disable compilation of the trio_fprintf() and
 * trio_fscanf() family of functions, or define to 1 to enable them.
 *
 * This may be useful on an embedded platform with no filesystem.
 * Note that trio_printf() uses fwrite to write to stdout, so if you
 * do not have an implementation of fwrite() at all then you must also
 * define TRIO_FEATURE_STDIO to 0.
 */
#if !defined(TRIO_FEATURE_FILE)
# define TRIO_FEATURE_FILE 1
#endif

/*
 * TRIO_FEATURE_STDIO (=0 or =1)
 *
 * Define this to 0 to disable compilation of the trio_printf() and
 * trio_scanf() family of functions, or define to 1 to enable them.
 *
 * This may be useful on an embedded platform with no standard I/O.
 */
#if !defined(TRIO_FEATURE_STDIO)
# define TRIO_FEATURE_STDIO 1
#endif

/*
 * TRIO_FEATURE_FD (=0 or =1)
 *
 * Define this to 0 to disable compilation of the trio_dprintf() and
 * trio_dscanf() family of functions, or define to 1 to enable them.
 *
 * This may be useful on an embedded platform with no filesystem, or on
 * a platform that supports file I/O using FILE* but not using raw file
 * descriptors.
 */
#if !defined(TRIO_FEATURE_FD)
# define TRIO_FEATURE_FD 1
#endif

/*
 * TRIO_FEATURE_DYNAMICSTRING (=0 or =1)
 *
 * Define this to 0 to disable compilation of the trio_aprintf() 
 * family of functions, or define to 1 to enable them.
 *
 * If you define both this and TRIO_MINIMAL to 0, then Trio will never
 * call malloc or free.
 */
#if !defined(TRIO_FEATURE_DYNAMICSTRING)
# define TRIO_FEATURE_DYNAMICSTRING 1
#endif

/*
 * TRIO_FEATURE_CLOSURE (=0 or =1)
 *
 * Define this to 0 to disable compilation of the trio_cprintf() and
 * trio_cscanf() family of functions, or define to 1 to enable them.
 *
 * These functions are rarely needed. This saves a (small) amount of code.
 */
#if !defined(TRIO_FEATURE_CLOSURE)
# define TRIO_FEATURE_CLOSURE 1
#endif

/*
 * TRIO_FEATURE_ERRORCODE (=0 or =1)
 *
 * Define this to 0 to return -1 from the print and scan function on
 * error, or define to 1 to return a negative number with debugging
 * information as part of the return code.
 *
 * If enabled, the return code will be a negative number, which encodes
 * an error code and an error location. These can be decoded with the
 * TRIO_ERROR_CODE and TRIO_ERROR_POSITION macros.
 */
#if defined(TRIO_ERRORS)
# define TRIO_FEATURE_ERRORCODE TRIO_ERRORS
#endif
#if !defined(TRIO_FEATURE_ERRORCODE)
# define TRIO_FEATURE_ERRORCODE 1
#endif

/*
 * TRIO_FEATURE_STRERR (=0 or =1)
 *
 * Define this to 0 if you do not use trio_strerror(), or define to 1 if
 * you do use it.
 *
 * This saves a (small) amount of code.
 */
#if !defined(TRIO_FEATURE_STRERR)
# define TRIO_FEATURE_STRERR 1
#endif

/*
 * TRIO_FEATURE_FLOAT (=0 or =1)
 *
 * Define this to 0 to disable all floating-point support, or define
 * to 1 to enable it.
 *
 * This is useful in restricted embedded platforms that do not support
 * floating-point.  Obviously you cannot use floating-point format
 * specifiers if you define this.
 *
 * Do not compile trionan.c if you disable this.
 */
#if !defined(TRIO_FEATURE_FLOAT)
# define TRIO_FEATURE_FLOAT 1
#endif

/*
 * TRIO_FEATURE_LOCALE (=0 or =1)
 *
 * Define this to 0 to disable customized locale support, or define
 * to 1 to enable it.
 *
 * This saves a (small) amount of code.
 */
#if !defined(TRIO_FEATURE_LOCALE)
# define TRIO_FEATURE_LOCALE 1
#endif

/*
 * TRIO_MINIMAL
 *
 * Define this to disable building the public trionan.h and triostr.h.
 * If you define this, then you must not compile trionan.c and triostr.c
 * separately.
 */
#if defined(TRIO_MINIMAL)
# if !defined(TRIO_EMBED_NAN)
#  define TRIO_EMBED_NAN
# endif
# if !defined(TRIO_EMBED_STRING)
#  define TRIO_EMBED_STRING
# endif
#endif
  
/* Does not work yet. Do not enable */
#ifndef TRIO_FEATURE_WIDECHAR
# define TRIO_FEATURE_WIDECHAR 0
#endif

/*************************************************************************
 * Mapping standards to internal features
 */

#if !defined(TRIO_FEATURE_HEXFLOAT)
# define TRIO_FEATURE_HEXFLOAT (TRIO_C99 && TRIO_FEATURE_FLOAT)
#endif

#if !defined(TRIO_FEATURE_LONGDOUBLE)
# define TRIO_FEATURE_LONGDOUBLE TRIO_FEATURE_FLOAT
#endif

#if !defined(TRIO_FEATURE_ERRNO)
# define TRIO_FEATURE_ERRNO TRIO_GNU
#endif

#if !defined(TRIO_FEATURE_QUAD)
# define TRIO_FEATURE_QUAD (TRIO_BSD || TRIO_GNU)
#endif

#if !defined(TRIO_FEATURE_SIZE_T)
# define TRIO_FEATURE_SIZE_T TRIO_C99
#endif

#if !defined(TRIO_FEATURE_SIZE_T_UPPER)
# define TRIO_FEATURE_SIZE_T_UPPER TRIO_GNU
#endif
  
#if !defined(TRIO_FEATURE_PTRDIFF_T)
# define TRIO_FEATURE_PTRDIFF_T TRIO_C99
#endif

#if !defined(TRIO_FEATURE_INTMAX_T)
# define TRIO_FEATURE_INTMAX_T TRIO_C99
#endif

#if !defined(TRIO_FEATURE_FIXED_SIZE)
# define TRIO_FEATURE_FIXED_SIZE TRIO_MICROSOFT
#endif

#if !defined(TRIO_FEATURE_POSITIONAL)
# define TRIO_FEATURE_POSITIONAL TRIO_UNIX98
#endif

#if !defined(TRIO_FEATURE_USER_DEFINED)
# define TRIO_FEATURE_USER_DEFINED TRIO_EXTENSION
#endif

#if !defined(TRIO_FEATURE_BINARY)
# define TRIO_FEATURE_BINARY TRIO_EXTENSION
#endif

#if !defined(TRIO_FEATURE_QUOTE)
# define TRIO_FEATURE_QUOTE TRIO_EXTENSION
#endif
  
#if !defined(TRIO_FEATURE_STICKY)
# define TRIO_FEATURE_STICKY TRIO_EXTENSION
#endif
  
#if !defined(TRIO_FEATURE_VARSIZE)
# define TRIO_FEATURE_VARSIZE TRIO_EXTENSION
#endif

#if !defined(TRIO_FEATURE_ROUNDING)
# define TRIO_FEATURE_ROUNDING TRIO_EXTENSION
#endif
  
/*************************************************************************
 * Memory handling
 */
#ifndef TRIO_MALLOC
# define TRIO_MALLOC(n) malloc(n)
#endif
#ifndef TRIO_REALLOC
# define TRIO_REALLOC(x,n) realloc((x),(n))
#endif
#ifndef TRIO_FREE
# define TRIO_FREE(x) free(x)
#endif


/*************************************************************************
 * User-defined specifiers
 */

typedef int (*trio_callback_t) TRIO_PROTO((trio_pointer_t));

trio_pointer_t trio_register TRIO_PROTO((trio_callback_t callback, const char *name));
void trio_unregister TRIO_PROTO((trio_pointer_t handle));

TRIO_CONST char *trio_get_format TRIO_PROTO((trio_pointer_t ref));
trio_pointer_t trio_get_argument TRIO_PROTO((trio_pointer_t ref));

/* Modifiers */
int  trio_get_width TRIO_PROTO((trio_pointer_t ref));
void trio_set_width TRIO_PROTO((trio_pointer_t ref, int width));
int  trio_get_precision TRIO_PROTO((trio_pointer_t ref));
void trio_set_precision TRIO_PROTO((trio_pointer_t ref, int precision));
int  trio_get_base TRIO_PROTO((trio_pointer_t ref));
void trio_set_base TRIO_PROTO((trio_pointer_t ref, int base));
int  trio_get_padding TRIO_PROTO((trio_pointer_t ref));
void trio_set_padding TRIO_PROTO((trio_pointer_t ref, int is_padding));
int  trio_get_short TRIO_PROTO((trio_pointer_t ref)); /* h */
void trio_set_shortshort TRIO_PROTO((trio_pointer_t ref, int is_shortshort));
int  trio_get_shortshort TRIO_PROTO((trio_pointer_t ref)); /* hh */
void trio_set_short TRIO_PROTO((trio_pointer_t ref, int is_short));
int  trio_get_long TRIO_PROTO((trio_pointer_t ref)); /* l */
void trio_set_long TRIO_PROTO((trio_pointer_t ref, int is_long));
int  trio_get_longlong TRIO_PROTO((trio_pointer_t ref)); /* ll */
void trio_set_longlong TRIO_PROTO((trio_pointer_t ref, int is_longlong));
int  trio_get_longdouble TRIO_PROTO((trio_pointer_t ref)); /* L */
void trio_set_longdouble TRIO_PROTO((trio_pointer_t ref, int is_longdouble));
int  trio_get_alternative TRIO_PROTO((trio_pointer_t ref)); /* # */
void trio_set_alternative TRIO_PROTO((trio_pointer_t ref, int is_alternative));
int  trio_get_alignment TRIO_PROTO((trio_pointer_t ref)); /* - */
void trio_set_alignment TRIO_PROTO((trio_pointer_t ref, int is_leftaligned));
int  trio_get_spacing TRIO_PROTO((trio_pointer_t ref)); /*  TRIO_PROTO((space) */
void trio_set_spacing TRIO_PROTO((trio_pointer_t ref, int is_space));
int  trio_get_sign TRIO_PROTO((trio_pointer_t ref)); /* + */
void trio_set_sign TRIO_PROTO((trio_pointer_t ref, int is_showsign));
#if TRIO_FEATURE_QUOTE
int  trio_get_quote TRIO_PROTO((trio_pointer_t ref)); /* ' */
void trio_set_quote TRIO_PROTO((trio_pointer_t ref, int is_quote));
#endif
int  trio_get_upper TRIO_PROTO((trio_pointer_t ref));
void trio_set_upper TRIO_PROTO((trio_pointer_t ref, int is_upper));
#if TRIO_FEATURE_INTMAX_T
int  trio_get_largest TRIO_PROTO((trio_pointer_t ref)); /* j */
void trio_set_largest TRIO_PROTO((trio_pointer_t ref, int is_largest));
#endif
#if TRIO_FEATURE_PTRDIFF_T
int  trio_get_ptrdiff TRIO_PROTO((trio_pointer_t ref)); /* t */
void trio_set_ptrdiff TRIO_PROTO((trio_pointer_t ref, int is_ptrdiff));
#endif
#if TRIO_FEATURE_SIZE_T
int  trio_get_size TRIO_PROTO((trio_pointer_t ref)); /* z / Z */
void trio_set_size TRIO_PROTO((trio_pointer_t ref, int is_size));
#endif

/* Printing */
int trio_print_ref TRIO_PROTO((trio_pointer_t ref, const char *format, ...));
int trio_vprint_ref TRIO_PROTO((trio_pointer_t ref, const char *format, va_list args));
int trio_printv_ref TRIO_PROTO((trio_pointer_t ref, const char *format, trio_pointer_t *args));

void trio_print_int TRIO_PROTO((trio_pointer_t ref, int number));
void trio_print_uint TRIO_PROTO((trio_pointer_t ref, unsigned int number));
/*  void trio_print_long TRIO_PROTO((trio_pointer_t ref, long number)); */
/*  void trio_print_ulong TRIO_PROTO((trio_pointer_t ref, unsigned long number)); */
void trio_print_double TRIO_PROTO((trio_pointer_t ref, double number));
void trio_print_string TRIO_PROTO((trio_pointer_t ref, char *string));
void trio_print_pointer TRIO_PROTO((trio_pointer_t ref, trio_pointer_t pointer));

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* TRIO_TRIOP_H */
