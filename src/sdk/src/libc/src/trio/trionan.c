

/*************************************************************************
 * Include files
 */
#include "triodef.h"
#include "trionan.h"

#include <math.h>
#include <string.h>
#include <limits.h>
#if !defined(TRIO_PLATFORM_SYMBIAN)
# include <float.h>
#endif
#if defined(TRIO_PLATFORM_UNIX)
# include <signal.h>
#endif
#if defined(TRIO_COMPILER_DECC)
# include <fp_class.h>
#endif
#include <assert.h>

#if defined(TRIO_DOCUMENTATION)
# include "doc/doc_nan.h"
#endif
/** @addtogroup SpecialQuantities
    @{
*/

/*************************************************************************
 * Definitions
 */

#if !defined(TRIO_PUBLIC_NAN)
# define TRIO_PUBLIC_NAN TRIO_PUBLIC
#endif
#if !defined(TRIO_PRIVATE_NAN)
# define TRIO_PRIVATE_NAN TRIO_PRIVATE
#endif

#define TRIO_TRUE (1 == 1)
#define TRIO_FALSE (0 == 1)

/*
 * We must enable IEEE floating-point on Alpha
 */
#if defined(__alpha) && !defined(_IEEE_FP)
# if defined(TRIO_COMPILER_DECC)
#  if defined(TRIO_PLATFORM_VMS)
#   error "Must be compiled with option /IEEE_MODE=UNDERFLOW_TO_ZERO/FLOAT=IEEE"
#  else
#   if !defined(_CFE)
#    error "Must be compiled with option -ieee"
#   endif
#  endif
# else
#  if defined(TRIO_COMPILER_GCC)
#   error "Must be compiled with option -mieee"
#  endif
# endif
#endif /* __alpha && ! _IEEE_FP */

/*
 * In ANSI/IEEE 754-1985 64-bits double format numbers have the
 * following properties (amoungst others)
 *
 *   o FLT_RADIX == 2: binary encoding
 *   o DBL_MAX_EXP == 1024: 11 bits exponent, where one bit is used
 *     to indicate special numbers (e.g. NaN and Infinity), so the
 *     maximum exponent is 10 bits wide (2^10 == 1024).
 *   o DBL_MANT_DIG == 53: The mantissa is 52 bits wide, but because
 *     numbers are normalized the initial binary 1 is represented
 *     implicitly (the so-called "hidden bit"), which leaves us with
 *     the ability to represent 53 bits wide mantissa.
 */
#if defined(__STDC_IEC_559__)
# define TRIO_IEEE_754
#else
# if (FLT_RADIX - 0 == 2) && (DBL_MAX_EXP - 0 == 1024) && (DBL_MANT_DIG - 0 == 53)
#  define TRIO_IEEE_754
# endif
#endif

/*
 * Determine which fpclassify_and_sign() function to use.
 */
#if defined(TRIO_FUNC_FPCLASSIFY_AND_SIGNBIT)
# if defined(PREDEF_STANDARD_C99) && defined(fpclassify)
#  define TRIO_FUNC_C99_FPCLASSIFY_AND_SIGNBIT
# else
#  if defined(TRIO_COMPILER_DECC)
#   define TRIO_FUNC_DECC_FPCLASSIFY_AND_SIGNBIT
#  else
#   if defined(TRIO_COMPILER_VISUALC) || defined(TRIO_COMPILER_BORLAND)
#    define TRIO_FUNC_MS_FPCLASSIFY_AND_SIGNBIT
#   else
#    if defined(TRIO_COMPILER_HP) && defined(FP_PLUS_NORM)
#     define TRIO_FUNC_HP_FPCLASSIFY_AND_SIGNBIT
#    else
#     if defined(TRIO_COMPILER_XLC) && defined(FP_PLUS_NORM)
#      define TRIO_FUNC_XLC_FPCLASSIFY_AND_SIGNBIT
#     else
#      define TRIO_FUNC_INTERNAL_FPCLASSIFY_AND_SIGNBIT
#     endif
#    endif
#   endif
#  endif
# endif
#endif

/*
 * Determine how to generate negative zero.
 */
#if defined(TRIO_FUNC_NZERO)
# if defined(TRIO_IEEE_754)
#  define TRIO_NZERO_IEEE_754
# else
#  define TRIO_NZERO_FALLBACK
# endif
#endif

/*
 * Determine how to generate positive infinity.
 */
#if defined(TRIO_FUNC_PINF)
# if defined(INFINITY) && defined(__STDC_IEC_559__)
#  define TRIO_PINF_C99_MACRO
# else
#  if defined(TRIO_IEEE_754)
#   define TRIO_PINF_IEEE_754
#  else
#   define TRIO_PINF_FALLBACK
#  endif
# endif
#endif

/*
 * Determine how to generate NaN.
 */
#if defined(TRIO_FUNC_NAN)
# if defined(PREDEF_STANDARD_C99) && !defined(TRIO_COMPILER_DECC)
#  define TRIO_NAN_C99_FUNCTION
# else
#  if defined(NAN) && defined(__STDC_IEC_559__)
#   define TRIO_NAN_C99_MACRO
#  else
#   if defined(TRIO_IEEE_754)
#    define TRIO_NAN_IEEE_754
#   else
#    define TRIO_NAN_FALLBACK
#   endif
#  endif
# endif
#endif

/*
 * Resolve internal dependencies.
 */
#if defined(TRIO_FUNC_INTERNAL_FPCLASSIFY_AND_SIGNBIT)
# define TRIO_FUNC_INTERNAL_ISNAN
# define TRIO_FUNC_INTERNAL_ISINF
# if defined(TRIO_IEEE_754)
#  define TRIO_FUNC_INTERNAL_IS_SPECIAL_QUANTITY
#  define TRIO_FUNC_INTERNAL_IS_NEGATIVE
# endif
#endif

#if defined(TRIO_NZERO_IEEE_754) \
 || defined(TRIO_PINF_IEEE_754) \
 || defined(TRIO_NAN_IEEE_754)
# define TRIO_FUNC_INTERNAL_MAKE_DOUBLE
#endif

#if defined(TRIO_FUNC_INTERNAL_ISNAN)
# if defined(PREDEF_STANDARD_XPG3)
#  define TRIO_INTERNAL_ISNAN_XPG3
# else
#  if defined(TRIO_IEEE_754)
#   define TRIO_INTERNAL_ISNAN_IEEE_754
#  else
#   define TRIO_INTERNAL_ISNAN_FALLBACK
#  endif
# endif
#endif

#if defined(TRIO_FUNC_INTERNAL_ISINF)
# if defined(TRIO_IEEE_754)
#  define TRIO_INTERNAL_ISINF_IEEE_754
# else
#  define TRIO_INTERNAL_ISINF_FALLBACK
# endif
#endif

/*************************************************************************
 * Constants
 */

#if !defined(TRIO_EMBED_NAN)
static TRIO_CONST char rcsid[] = "@(#)$Id: trionan.c,v 1.33 2005/05/29 11:57:25 breese Exp $";
#endif

#if defined(TRIO_FUNC_INTERNAL_MAKE_DOUBLE) \
 || defined(TRIO_FUNC_INTERNAL_IS_SPECIAL_QUANTITY) \
 || defined(TRIO_FUNC_INTERNAL_IS_NEGATIVE)
/*
 * Endian-agnostic indexing macro.
 *
 * The value of internalEndianMagic, when converted into a 64-bit
 * integer, becomes 0x0706050403020100 (we could have used a 64-bit
 * integer value instead of a double, but not all platforms supports
 * that type). The value is automatically encoded with the correct
 * endianess by the compiler, which means that we can support any
 * kind of endianess. The individual bytes are then used as an index
 * for the IEEE 754 bit-patterns and masks.
 */
#define TRIO_DOUBLE_INDEX(x) (((unsigned char *)&internalEndianMagic)[7-(x)])
static TRIO_CONST double internalEndianMagic = 7.949928895127363e-275;
#endif

#if defined(TRIO_FUNC_INTERNAL_IS_SPECIAL_QUANTITY)
/* Mask for the exponent */
static TRIO_CONST unsigned char ieee_754_exponent_mask[] = {
  0x7F, 0xF0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

/* Mask for the mantissa */
static TRIO_CONST unsigned char ieee_754_mantissa_mask[] = {
  0x00, 0x0F, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF
};
#endif

#if defined(TRIO_FUNC_INTERNAL_IS_NEGATIVE)
/* Mask for the sign bit */
static TRIO_CONST unsigned char ieee_754_sign_mask[] = {
  0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};
#endif

#if defined(TRIO_NZERO_IEEE_754)
/* Bit-pattern for negative zero */
static TRIO_CONST unsigned char ieee_754_negzero_array[] = {
  0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};
#endif

#if defined(TRIO_PINF_IEEE_754)
/* Bit-pattern for infinity */
static TRIO_CONST unsigned char ieee_754_infinity_array[] = {
  0x7F, 0xF0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};
#endif

#if defined(TRIO_NAN_IEEE_754)
/* Bit-pattern for quiet NaN */
static TRIO_CONST unsigned char ieee_754_qnan_array[] = {
  0x7F, 0xF8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};
#endif


/*************************************************************************
 * Internal functions
 */

/*
 * internal_make_double
 */
#if defined(TRIO_FUNC_INTERNAL_MAKE_DOUBLE)

TRIO_PRIVATE_NAN double
internal_make_double
TRIO_ARGS1((values),
	   TRIO_CONST unsigned char *values)
{
  TRIO_VOLATILE double result;
  int i;

  for (i = 0; i < (int)sizeof(double); i++) {
    ((TRIO_VOLATILE unsigned char *)&result)[TRIO_DOUBLE_INDEX(i)] = values[i];
  }
  return result;
}

#endif

/*
 * internal_is_special_quantity
 */
#if defined(TRIO_FUNC_INTERNAL_IS_SPECIAL_QUANTITY)

TRIO_PRIVATE_NAN int
internal_is_special_quantity
TRIO_ARGS2((number, has_mantissa),
	   double number,
	   int *has_mantissa)
{
  unsigned int i;
  unsigned char current;
  int is_special_quantity = TRIO_TRUE;

  *has_mantissa = 0;

  for (i = 0; i < (unsigned int)sizeof(double); i++) {
    current = ((unsigned char *)&number)[TRIO_DOUBLE_INDEX(i)];
    is_special_quantity
      &= ((current & ieee_754_exponent_mask[i]) == ieee_754_exponent_mask[i]);
    *has_mantissa |= (current & ieee_754_mantissa_mask[i]);
  }
  return is_special_quantity;
}

#endif

/*
 * internal_is_negative
 */
#if defined(TRIO_FUNC_INTERNAL_IS_NEGATIVE)

TRIO_PRIVATE_NAN int
internal_is_negative
TRIO_ARGS1((number),
	   double number)
{
  unsigned int i;
  int is_negative = TRIO_FALSE;

  for (i = 0; i < (unsigned int)sizeof(double); i++) {
    is_negative |= (((unsigned char *)&number)[TRIO_DOUBLE_INDEX(i)]
		    & ieee_754_sign_mask[i]);
  }
  return is_negative;
}

#endif

#if defined(TRIO_FUNC_C99_FPCLASSIFY_AND_SIGNBIT)

TRIO_PRIVATE_NAN TRIO_INLINE int
c99_fpclassify_and_signbit
TRIO_ARGS2((number, is_negative),
	   double number,
	   int *is_negative)
{
  *is_negative = signbit(number);
  switch (fpclassify(number)) {
  case FP_NAN:
    return TRIO_FP_NAN;
  case FP_INFINITE:
    return TRIO_FP_INFINITE;
  case FP_SUBNORMAL:
    return TRIO_FP_SUBNORMAL;
  case FP_ZERO:
    return TRIO_FP_ZERO;
  default:
    return TRIO_FP_NORMAL;
  }
}

#endif /* TRIO_FUNC_C99_FPCLASSIFY_AND_SIGNBIT */

#if defined(TRIO_FUNC_DECC_FPCLASSIFY_AND_SIGNBIT)

TRIO_PRIVATE_NAN TRIO_INLINE int
decc_fpclassify_and_signbit
TRIO_ARGS2((number, is_negative),
	  double number,
	  int *is_negative)
{
  switch (fp_class(number)) {
  case FP_QNAN:
  case FP_SNAN:
    *is_negative = TRIO_FALSE; /* NaN has no sign */
    return TRIO_FP_NAN;
  case FP_POS_INF:
    *is_negative = TRIO_FALSE;
    return TRIO_FP_INFINITE;
  case FP_NEG_INF:
    *is_negative = TRIO_TRUE;
    return TRIO_FP_INFINITE;
  case FP_POS_DENORM:
    *is_negative = TRIO_FALSE;
    return TRIO_FP_SUBNORMAL;
  case FP_NEG_DENORM:
    *is_negative = TRIO_TRUE;
    return TRIO_FP_SUBNORMAL;
  case FP_POS_ZERO:
    *is_negative = TRIO_FALSE;
    return TRIO_FP_ZERO;
  case FP_NEG_ZERO:
    *is_negative = TRIO_TRUE;
    return TRIO_FP_ZERO;
  case FP_POS_NORM:
    *is_negative = TRIO_FALSE;
    return TRIO_FP_NORMAL;
  case FP_NEG_NORM:
    *is_negative = TRIO_TRUE;
    return TRIO_FP_NORMAL;
  default:
    *is_negative = (number < 0.0);
    return TRIO_FP_NORMAL;
  }
}

#endif /* TRIO_FUNC_DECC_FPCLASSIFY_AND_SIGNBIT */

#if defined(TRIO_FUNC_MS_FPCLASSIFY_AND_SIGNBIT)

TRIO_PRIVATE_NAN int
ms_fpclassify_and_signbit
TRIO_ARGS2((number, is_negative),
	  double number,
	  int *is_negative)
{
  int result;
# if defined(TRIO_COMPILER_BORLAND)
  /*
   * The floating-point precision may be changed by the Borland _fpclass()
   * function, so we have to save and restore the floating-point control mask.
   */
  unsigned int mask;
  /* Remember the old mask */
  mask = _control87(0, 0);
# endif
  
  switch (_fpclass(number)) {
  case _FPCLASS_QNAN:
  case _FPCLASS_SNAN:
    *is_negative = TRIO_FALSE; /* NaN has no sign */
    result = TRIO_FP_NAN;
    break;
  case _FPCLASS_PINF:
    *is_negative = TRIO_FALSE;
    result = TRIO_FP_INFINITE;
    break;
  case _FPCLASS_NINF:
    *is_negative = TRIO_TRUE;
    result = TRIO_FP_INFINITE;
    break;
  case _FPCLASS_PD:
    *is_negative = TRIO_FALSE;
    result = TRIO_FP_SUBNORMAL;
    break;
  case _FPCLASS_ND:
    *is_negative = TRIO_TRUE;
    result = TRIO_FP_SUBNORMAL;
    break;
  case _FPCLASS_PZ:
    *is_negative = TRIO_FALSE;
    result = TRIO_FP_ZERO;
    break;
  case _FPCLASS_NZ:
    *is_negative = TRIO_TRUE;
    result = TRIO_FP_ZERO;
    break;
  case _FPCLASS_PN:
    *is_negative = TRIO_FALSE;
    result = TRIO_FP_NORMAL;
    break;
  case _FPCLASS_NN:
    *is_negative = TRIO_TRUE;
    result = TRIO_FP_NORMAL;
    break;
  default:
    *is_negative = (number < 0.0);
    result = TRIO_FP_NORMAL;
    break;
  }
  
# if defined(TRIO_COMPILER_BORLAND)
  /* Restore the old precision */
  (void)_control87(mask, MCW_PC);
# endif
  
  return result;
}

#endif /* TRIO_FUNC_MS_FPCLASSIFY_AND_SIGNBIT */

#if defined(TRIO_FUNC_HP_FPCLASSIFY_AND_SIGNBIT)

TRIO_PRIVATE_NAN TRIO_INLINE int
hp_fpclassify_and_signbit
TRIO_ARGS2((number, is_negative),
	  double number,
	  int *is_negative)
{
  /*
   * HP-UX 9.x and 10.x have an fpclassify() function, that is different
   * from the C99 fpclassify() macro supported on HP-UX 11.x.
   */
  switch (fpclassify(number)) {
  case FP_QNAN:
  case FP_SNAN:
    *is_negative = TRIO_FALSE; /* NaN has no sign */
    return TRIO_FP_NAN;
  case FP_PLUS_INF:
    *is_negative = TRIO_FALSE;
    return TRIO_FP_INFINITE;
  case FP_MINUS_INF:
    *is_negative = TRIO_TRUE;
    return TRIO_FP_INFINITE;
  case FP_PLUS_DENORM:
    *is_negative = TRIO_FALSE;
    return TRIO_FP_SUBNORMAL;
  case FP_MINUS_DENORM:
    *is_negative = TRIO_TRUE;
    return TRIO_FP_SUBNORMAL;
  case FP_PLUS_ZERO:
    *is_negative = TRIO_FALSE;
    return TRIO_FP_ZERO;
  case FP_MINUS_ZERO:
    *is_negative = TRIO_TRUE;
    return TRIO_FP_ZERO;
  case FP_PLUS_NORM:
    *is_negative = TRIO_FALSE;
    return TRIO_FP_NORMAL;
  case FP_MINUS_NORM:
    *is_negative = TRIO_TRUE;
    return TRIO_FP_NORMAL;
  default:
    *is_negative = (number < 0.0);
    return TRIO_FP_NORMAL;
  }
}

#endif /* TRIO_FUNC_HP_FPCLASSIFY_AND_SIGNBIT */

#if defined(TRIO_FUNC_XLC_FPCLASSIFY_AND_SIGNBIT)

TRIO_PRIVATE_NAN TRIO_INLINE int
xlc_fpclassify_and_signbit
TRIO_ARGS2((number, is_negative),
	  double number,
	  int *is_negative)
{
  /*
   * AIX has class() for C, and _class() for C++
   */
# if defined(__cplusplus)
#  define AIX_CLASS(n) _class(n)
# else
#  define AIX_CLASS(n) class(n)
# endif

  switch (AIX_CLASS(number)) {
  case FP_QNAN:
  case FP_SNAN:
    *is_negative = TRIO_FALSE; /* NaN has no sign */
    return TRIO_FP_NAN;
  case FP_PLUS_INF:
    *is_negative = TRIO_FALSE;
    return TRIO_FP_INFINITE;
  case FP_MINUS_INF:
    *is_negative = TRIO_TRUE;
    return TRIO_FP_INFINITE;
  case FP_PLUS_DENORM:
    *is_negative = TRIO_FALSE;
    return TRIO_FP_SUBNORMAL;
  case FP_MINUS_DENORM:
    *is_negative = TRIO_TRUE;
    return TRIO_FP_SUBNORMAL;
  case FP_PLUS_ZERO:
    *is_negative = TRIO_FALSE;
    return TRIO_FP_ZERO;
  case FP_MINUS_ZERO:
    *is_negative = TRIO_TRUE;
    return TRIO_FP_ZERO;
  case FP_PLUS_NORM:
    *is_negative = TRIO_FALSE;
    return TRIO_FP_NORMAL;
  case FP_MINUS_NORM:
    *is_negative = TRIO_TRUE;
    return TRIO_FP_NORMAL;
  default:
    *is_negative = (number < 0.0);
    return TRIO_FP_NORMAL;
  }
}

#endif /* TRIO_FUNC_XLC_FPCLASSIFY_AND_SIGNBIT */

#if defined(TRIO_FUNC_INTERNAL_ISNAN)

TRIO_PRIVATE_NAN TRIO_INLINE int
internal_isnan
TRIO_ARGS1((number),
	   double number)
{
# if defined(TRIO_INTERNAL_ISNAN_XPG3) || defined(TRIO_PLATFORM_SYMBIAN)
  /*
   * XPG3 defines isnan() as a function.
   */
  return isnan(number);

# endif
  
# if defined(TRIO_INTERNAL_ISNAN_IEEE_754)
  
  /*
   * Examine IEEE 754 bit-pattern. A NaN must have a special exponent
   * pattern, and a non-empty mantissa.
   */
  int has_mantissa;
  int is_special_quantity;

  is_special_quantity = internal_is_special_quantity(number, &has_mantissa);
  
  return (is_special_quantity && has_mantissa);
  
# endif

# if defined(TRIO_INTERNAL_ISNAN_FALLBACK)
  
  /*
   * Fallback solution
   */
  int status;
  double integral, fraction;
  
#  if defined(TRIO_PLATFORM_UNIX)
  void (*signal_handler)(int) = signal(SIGFPE, SIG_IGN);
#  endif
  
  status = (/*
	     * NaN is the only number which does not compare to itself
	     */
	    ((TRIO_VOLATILE double)number != (TRIO_VOLATILE double)number) ||
	    /*
	     * Fallback solution if NaN compares to NaN
	     */
	    ((number != 0.0) &&
	     (fraction = modf(number, &integral),
	      integral == fraction)));
  
#  if defined(TRIO_PLATFORM_UNIX)
  signal(SIGFPE, signal_handler);
#  endif
  
  return status;
  
# endif
}

#endif /* TRIO_FUNC_INTERNAL_ISNAN */

#if defined(TRIO_FUNC_INTERNAL_ISINF)

TRIO_PRIVATE_NAN TRIO_INLINE int
internal_isinf
TRIO_ARGS1((number),
	   double number)
{
# if defined(TRIO_PLATFORM_SYMBIAN)

  return isinf(number);

# endif

# if defined(TRIO_INTERNAL_ISINF_IEEE_754)
  /*
   * Examine IEEE 754 bit-pattern. Infinity must have a special exponent
   * pattern, and an empty mantissa.
   */
  int has_mantissa;
  int is_special_quantity;

  is_special_quantity = internal_is_special_quantity(number, &has_mantissa);
  
  return (is_special_quantity && !has_mantissa)
    ? ((number < 0.0) ? -1 : 1)
    : 0;

# endif

# if defined(TRIO_INTERNAL_ISINF_FALLBACK)
  
  /*
   * Fallback solution.
   */
  int status;
  
#  if defined(TRIO_PLATFORM_UNIX)
  void (*signal_handler)(int) = signal(SIGFPE, SIG_IGN);
#  endif
  
  double infinity = trio_pinf();
  
  status = ((number == infinity)
	    ? 1
	    : ((number == -infinity) ? -1 : 0));
  
#  if defined(TRIO_PLATFORM_UNIX)
  signal(SIGFPE, signal_handler);
#  endif
  
  return status;

# endif
}

#endif /* TRIO_FUNC_INTERNAL_ISINF */

/*************************************************************************
 * Public functions
 */

#if defined(TRIO_FUNC_FPCLASSIFY_AND_SIGNBIT)

TRIO_PUBLIC_NAN int
trio_fpclassify_and_signbit
TRIO_ARGS2((number, is_negative),
	   double number,
	   int *is_negative)
{
  /* The TRIO_FUNC_xxx_FPCLASSIFY_AND_SIGNBIT macros are mutually exclusive */
  
#if defined(TRIO_FUNC_C99_FPCLASSIFY_AND_SIGNBIT)

  return c99_fpclassify_and_signbit(number, is_negative);

#endif

#if defined(TRIO_FUNC_DECC_FPCLASSIFY_AND_SIGNBIT)

  return decc_fpclassify_and_signbit(number, is_negative);

#endif

#if defined(TRIO_FUNC_MS_FPCLASSIFY_AND_SIGNBIT)

  return ms_fpclassify_and_signbit(number, is_negative);

#endif

#if defined(TRIO_FUNC_HP_FPCLASSIFY_AND_SIGNBIT)

  return hp_fpclassify_and_signbit(number, is_negative);

#endif

#if defined(TRIO_FUNC_XLC_FPCLASSIFY_AND_SIGNBIT)

  return xlc_fpclassify_and_signbit(number, is_negative);

#endif

#if defined(TRIO_FUNC_INTERNAL_FPCLASSIFY_AND_SIGNBIT)
  
  /*
   * Fallback solution.
   */
  int rc;
  
  if (number == 0.0) {
    /*
     * In IEEE 754 the sign of zero is ignored in comparisons, so we
     * have to handle this as a special case by examining the sign bit
     * directly.
     */
# if defined(TRIO_IEEE_754)
    *is_negative = internal_is_negative(number);
# else
    *is_negative = TRIO_FALSE; /* FIXME */
# endif
    return TRIO_FP_ZERO;
  }
  if (internal_isnan(number)) {
    *is_negative = TRIO_FALSE;
    return TRIO_FP_NAN;
  }
  rc = internal_isinf(number);
  if (rc != 0) {
    *is_negative = (rc == -1);
    return TRIO_FP_INFINITE;
  }
  if ((number > 0.0) && (number < DBL_MIN)) {
    *is_negative = TRIO_FALSE;
    return TRIO_FP_SUBNORMAL;
  }
  if ((number < 0.0) && (number > -DBL_MIN)) {
    *is_negative = TRIO_TRUE;
    return TRIO_FP_SUBNORMAL;
  }
  *is_negative = (number < 0.0);
  return TRIO_FP_NORMAL;

#endif
}

#endif

/**
   Check for NaN.

   @param number An arbitrary floating-point number.
   @return Boolean value indicating whether or not the number is a NaN.
*/
#if defined(TRIO_FUNC_ISNAN)

TRIO_PUBLIC_NAN int
trio_isnan
TRIO_ARGS1((number),
	   double number)
{
  int dummy;
  
  return (trio_fpclassify_and_signbit(number, &dummy) == TRIO_FP_NAN);
}

#endif

/**
   Check for infinity.

   @param number An arbitrary floating-point number.
   @return 1 if positive infinity, -1 if negative infinity, 0 otherwise.
*/
#if defined(TRIO_FUNC_ISINF)

TRIO_PUBLIC_NAN int
trio_isinf
TRIO_ARGS1((number),
	   double number)
{
  int is_negative;
  
  if (trio_fpclassify_and_signbit(number, &is_negative) == TRIO_FP_INFINITE)
    {
      return (is_negative) ? -1 : 1;
    }
  else
    {
      return 0;
    }
}

#endif

/**
   Check for finity.

   @param number An arbitrary floating-point number.
   @return Boolean value indicating whether or not the number is a finite.
*/
#if defined(TRIO_FUNC_ISFINITE)

TRIO_PUBLIC_NAN int
trio_isfinite
TRIO_ARGS1((number),
	   double number)
{
  int dummy;
  
  switch (trio_fpclassify_and_signbit(number, &dummy))
    {
    case TRIO_FP_INFINITE:
    case TRIO_FP_NAN:
      return 0;
    default:
      return 1;
    }
}

#endif

/**
   Examine the sign of a number.

   @param number An arbitrary floating-point number.
   @return Boolean value indicating whether or not the number has the
   sign bit set (i.e. is negative).
*/
#if defined(TRIO_FUNC_SIGNBIT)

TRIO_PUBLIC_NAN int
trio_signbit
TRIO_ARGS1((number),
	   double number)
{
  int is_negative;
  
  (void)trio_fpclassify_and_signbit(number, &is_negative);
  return is_negative;
}

#endif

/**
   Examine the class of a number.

   @param number An arbitrary floating-point number.
   @return Enumerable value indicating the class of @p number
*/
#if defined(TRIO_FUNC_FPCLASSIFY)

TRIO_PUBLIC_NAN int
trio_fpclassify
TRIO_ARGS1((number),
	   double number)
{
  int dummy;
  
  return trio_fpclassify_and_signbit(number, &dummy);
}

#endif

/**
   Generate negative zero.

   @return Floating-point representation of negative zero.
*/
#if defined(TRIO_FUNC_NZERO)

TRIO_PUBLIC_NAN double
trio_nzero(TRIO_NOARGS)
{
# if defined(TRIO_NZERO_IEEE_754)
  
  return internal_make_double(ieee_754_negzero_array);

# endif
  
# if defined(TRIO_NZERO_FALLBACK)
  
  TRIO_VOLATILE double zero = 0.0;

  return -zero;
  
# endif
}

#endif

/**
   Generate positive infinity.

   @return Floating-point representation of positive infinity.
*/
#if defined(TRIO_FUNC_PINF)

TRIO_PUBLIC_NAN double
trio_pinf(TRIO_NOARGS)
{
  /* Cache the result */
  static double pinf_value = 0.0;

  if (pinf_value == 0.0) {

# if defined(TRIO_PINF_C99_MACRO)
    
    pinf_value = (double)INFINITY;

# endif
    
# if defined(TRIO_PINF_IEEE_754)
    
    pinf_value = internal_make_double(ieee_754_infinity_array);

# endif

# if defined(TRIO_PINF_FALLBACK)
    /*
     * If HUGE_VAL is different from DBL_MAX, then HUGE_VAL is used
     * as infinity. Otherwise we have to resort to an overflow
     * operation to generate infinity.
     */
#  if defined(TRIO_PLATFORM_UNIX)
    void (*signal_handler)(int) = signal(SIGFPE, SIG_IGN);
#  endif

    pinf_value = HUGE_VAL;
    if (HUGE_VAL == DBL_MAX) {
      /* Force overflow */
      pinf_value += HUGE_VAL;
    }
    
#  if defined(TRIO_PLATFORM_UNIX)
    signal(SIGFPE, signal_handler);
#  endif

# endif
  }
  return pinf_value;
}

#endif

/**
   Generate negative infinity.

   @return Floating-point value of negative infinity.
*/
#if defined(TRIO_FUNC_NINF)

TRIO_PUBLIC_NAN double
trio_ninf(TRIO_NOARGS)
{
  static double ninf_value = 0.0;

  if (ninf_value == 0.0) {
    /*
     * Negative infinity is calculated by negating positive infinity,
     * which can be done because it is legal to do calculations on
     * infinity (for example,  1 / infinity == 0).
     */
    ninf_value = -trio_pinf();
  }
  return ninf_value;
}

#endif

/**
   Generate NaN.

   @return Floating-point representation of NaN.
*/
#if defined(TRIO_FUNC_NAN)

TRIO_PUBLIC_NAN double
trio_nan(TRIO_NOARGS)
{
  /* Cache the result */
  static double nan_value = 0.0;

  if (nan_value == 0.0) {
    
# if defined(TRIO_NAN_C99_FUNCTION) || defined(TRIO_PLATFORM_SYMBIAN)
    
    nan_value = nan("");

# endif
    
# if defined(TRIO_NAN_C99_MACRO)
    
    nan_value = (double)NAN;

# endif

# if defined(TRIO_NAN_IEEE_754)
    
    nan_value = internal_make_double(ieee_754_qnan_array);

# endif
    
# if defined(TRIO_NAN_FALLBACK)
    /*
     * There are several ways to generate NaN. The one used here is
     * to divide infinity by infinity. I would have preferred to add
     * negative infinity to positive infinity, but that yields wrong
     * result (infinity) on FreeBSD.
     *
     * This may fail if the hardware does not support NaN, or if
     * the Invalid Operation floating-point exception is unmasked.
     */
#  if defined(TRIO_PLATFORM_UNIX)
    void (*signal_handler)(int) = signal(SIGFPE, SIG_IGN);
#  endif
    
    nan_value = trio_pinf() / trio_pinf();
    
#  if defined(TRIO_PLATFORM_UNIX)
    signal(SIGFPE, signal_handler);
#  endif

# endif
  }
  return nan_value;
}

#endif

/** @} SpecialQuantities */

/*************************************************************************
 * For test purposes.
 *
 * Add the following compiler option to include this test code.
 *
 *  Unix : -DSTANDALONE
 *  VMS  : /DEFINE=(STANDALONE)
 */
#if defined(STANDALONE)
# include <stdio.h>

static TRIO_CONST char *
getClassification
TRIO_ARGS1((type),
	   int type)
{
  switch (type) {
  case TRIO_FP_INFINITE:
    return "FP_INFINITE";
  case TRIO_FP_NAN:
    return "FP_NAN";
  case TRIO_FP_NORMAL:
    return "FP_NORMAL";
  case TRIO_FP_SUBNORMAL:
    return "FP_SUBNORMAL";
  case TRIO_FP_ZERO:
    return "FP_ZERO";
  default:
    return "FP_UNKNOWN";
  }
}

static void
print_class
TRIO_ARGS2((prefix, number),
	   TRIO_CONST char *prefix,
	   double number)
{
  printf("%-6s: %s %-15s %g\n",
	 prefix,
	 trio_signbit(number) ? "-" : "+",
	 getClassification(trio_fpclassify(number)),
	 number);
}

int main(TRIO_NOARGS)
{
  double my_nan;
  double my_pinf;
  double my_ninf;
# if defined(TRIO_PLATFORM_UNIX)
  void (*signal_handler) TRIO_PROTO((int));
# endif

  my_nan = trio_nan();
  my_pinf = trio_pinf();
  my_ninf = trio_ninf();

  print_class("Nan", my_nan);
  print_class("PInf", my_pinf);
  print_class("NInf", my_ninf);
  print_class("PZero", 0.0);
  print_class("NZero", -0.0);
  print_class("PNorm", 1.0);
  print_class("NNorm", -1.0);
  print_class("PSub", 1.01e-307 - 1.00e-307);
  print_class("NSub", 1.00e-307 - 1.01e-307);
  
  printf("NaN : %4g 0x%02x%02x%02x%02x%02x%02x%02x%02x (%2d, %2d, %2d)\n",
	 my_nan,
	 ((unsigned char *)&my_nan)[0],
	 ((unsigned char *)&my_nan)[1],
	 ((unsigned char *)&my_nan)[2],
	 ((unsigned char *)&my_nan)[3],
	 ((unsigned char *)&my_nan)[4],
	 ((unsigned char *)&my_nan)[5],
	 ((unsigned char *)&my_nan)[6],
	 ((unsigned char *)&my_nan)[7],
	 trio_isnan(my_nan), trio_isinf(my_nan), trio_isfinite(my_nan));
  printf("PInf: %4g 0x%02x%02x%02x%02x%02x%02x%02x%02x (%2d, %2d, %2d)\n",
	 my_pinf,
	 ((unsigned char *)&my_pinf)[0],
	 ((unsigned char *)&my_pinf)[1],
	 ((unsigned char *)&my_pinf)[2],
	 ((unsigned char *)&my_pinf)[3],
	 ((unsigned char *)&my_pinf)[4],
	 ((unsigned char *)&my_pinf)[5],
	 ((unsigned char *)&my_pinf)[6],
	 ((unsigned char *)&my_pinf)[7],
	 trio_isnan(my_pinf), trio_isinf(my_pinf), trio_isfinite(my_pinf));
  printf("NInf: %4g 0x%02x%02x%02x%02x%02x%02x%02x%02x (%2d, %2d, %2d)\n",
	 my_ninf,
	 ((unsigned char *)&my_ninf)[0],
	 ((unsigned char *)&my_ninf)[1],
	 ((unsigned char *)&my_ninf)[2],
	 ((unsigned char *)&my_ninf)[3],
	 ((unsigned char *)&my_ninf)[4],
	 ((unsigned char *)&my_ninf)[5],
	 ((unsigned char *)&my_ninf)[6],
	 ((unsigned char *)&my_ninf)[7],
	 trio_isnan(my_ninf), trio_isinf(my_ninf), trio_isfinite(my_ninf));
  
# if defined(TRIO_PLATFORM_UNIX)
  signal_handler = signal(SIGFPE, SIG_IGN);
# endif
  
  my_pinf = DBL_MAX + DBL_MAX;
  my_ninf = -my_pinf;
  my_nan = my_pinf / my_pinf;

# if defined(TRIO_PLATFORM_UNIX)
  signal(SIGFPE, signal_handler);
# endif
  
  printf("NaN : %4g 0x%02x%02x%02x%02x%02x%02x%02x%02x (%2d, %2d, %2d)\n",
	 my_nan,
	 ((unsigned char *)&my_nan)[0],
	 ((unsigned char *)&my_nan)[1],
	 ((unsigned char *)&my_nan)[2],
	 ((unsigned char *)&my_nan)[3],
	 ((unsigned char *)&my_nan)[4],
	 ((unsigned char *)&my_nan)[5],
	 ((unsigned char *)&my_nan)[6],
	 ((unsigned char *)&my_nan)[7],
	 trio_isnan(my_nan), trio_isinf(my_nan), trio_isfinite(my_nan));
  printf("PInf: %4g 0x%02x%02x%02x%02x%02x%02x%02x%02x (%2d, %2d, %2d)\n",
	 my_pinf,
	 ((unsigned char *)&my_pinf)[0],
	 ((unsigned char *)&my_pinf)[1],
	 ((unsigned char *)&my_pinf)[2],
	 ((unsigned char *)&my_pinf)[3],
	 ((unsigned char *)&my_pinf)[4],
	 ((unsigned char *)&my_pinf)[5],
	 ((unsigned char *)&my_pinf)[6],
	 ((unsigned char *)&my_pinf)[7],
	 trio_isnan(my_pinf), trio_isinf(my_pinf), trio_isfinite(my_pinf));
  printf("NInf: %4g 0x%02x%02x%02x%02x%02x%02x%02x%02x (%2d, %2d, %2d)\n",
	 my_ninf,
	 ((unsigned char *)&my_ninf)[0],
	 ((unsigned char *)&my_ninf)[1],
	 ((unsigned char *)&my_ninf)[2],
	 ((unsigned char *)&my_ninf)[3],
	 ((unsigned char *)&my_ninf)[4],
	 ((unsigned char *)&my_ninf)[5],
	 ((unsigned char *)&my_ninf)[6],
	 ((unsigned char *)&my_ninf)[7],
	 trio_isnan(my_ninf), trio_isinf(my_ninf), trio_isfinite(my_ninf));
  
  return 0;
}
#endif
