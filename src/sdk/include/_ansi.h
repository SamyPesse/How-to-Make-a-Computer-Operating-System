

#ifndef	_ANSIDECL_H_
#define	_ANSIDECL_H_



/*  ISO C++.  */

#ifdef __cplusplus
#if !(defined(_BEGIN_STD_C) && defined(_END_STD_C))
#ifdef _HAVE_STD_CXX
#define _BEGIN_STD_C namespace std { extern "C" {
#define _END_STD_C  } }
#else
#define _BEGIN_STD_C extern "C" {
#define _END_STD_C  }
#endif
#if defined(__GNUC__) && \
  ( (__GNUC__ >= 4) || \
    ( (__GNUC__ >= 3) && defined(__GNUC_MINOR__) && (__GNUC_MINOR__ >= 3) ) )
#define _NOTHROW __attribute__ ((nothrow))
#else
#define _NOTHROW throw()
#endif
#endif
#else
#define _BEGIN_STD_C
#define _END_STD_C
#define _NOTHROW
#endif


#endif /* _ANSIDECL_H_ */
