

/*
 * ISO C Standard:  5.2.4.2.2  Characteristics of floating types <float.h>
 */

#ifndef _FLOAT_H___
#define _FLOAT_H___

/* Radix of exponent representation, b. */
#undef FLT_RADIX
#define FLT_RADIX	__FLT_RADIX__

/* Number of base-FLT_RADIX digits in the significand, p.  */
#undef FLT_MANT_DIG
#undef DBL_MANT_DIG
#undef LDBL_MANT_DIG
#define FLT_MANT_DIG	__FLT_MANT_DIG__
#define DBL_MANT_DIG	__DBL_MANT_DIG__
#define LDBL_MANT_DIG	__LDBL_MANT_DIG__

/* Number of decimal digits, q, such that any floating-point number with q
   decimal digits can be rounded into a floating-point number with p radix b
   digits and back again without change to the q decimal digits,

	p * log10(b)			if b is a power of 10
	floor((p - 1) * log10(b))	otherwise
*/
#undef FLT_DIG
#undef DBL_DIG
#undef LDBL_DIG
#define FLT_DIG		__FLT_DIG__
#define DBL_DIG		__DBL_DIG__
#define LDBL_DIG	__LDBL_DIG__

/* Minimum int x such that FLT_RADIX**(x-1) is a normalized float, emin */
#undef FLT_MIN_EXP
#undef DBL_MIN_EXP
#undef LDBL_MIN_EXP
#define FLT_MIN_EXP	__FLT_MIN_EXP__
#define DBL_MIN_EXP	__DBL_MIN_EXP__
#define LDBL_MIN_EXP	__LDBL_MIN_EXP__

/* Minimum negative integer such that 10 raised to that power is in the
   range of normalized floating-point numbers,

	ceil(log10(b) * (emin - 1))
*/
#undef FLT_MIN_10_EXP
#undef DBL_MIN_10_EXP
#undef LDBL_MIN_10_EXP
#define FLT_MIN_10_EXP	__FLT_MIN_10_EXP__
#define DBL_MIN_10_EXP	__DBL_MIN_10_EXP__
#define LDBL_MIN_10_EXP	__LDBL_MIN_10_EXP__

/* Maximum int x such that FLT_RADIX**(x-1) is a representable float, emax.  */
#undef FLT_MAX_EXP
#undef DBL_MAX_EXP
#undef LDBL_MAX_EXP
#define FLT_MAX_EXP	__FLT_MAX_EXP__
#define DBL_MAX_EXP	__DBL_MAX_EXP__
#define LDBL_MAX_EXP	__LDBL_MAX_EXP__

/* Maximum integer such that 10 raised to that power is in the range of
   representable finite floating-point numbers,

	floor(log10((1 - b**-p) * b**emax))
*/
#undef FLT_MAX_10_EXP
#undef DBL_MAX_10_EXP
#undef LDBL_MAX_10_EXP
#define FLT_MAX_10_EXP	__FLT_MAX_10_EXP__
#define DBL_MAX_10_EXP	__DBL_MAX_10_EXP__
#define LDBL_MAX_10_EXP	__LDBL_MAX_10_EXP__

/* Maximum representable finite floating-point number,

	(1 - b**-p) * b**emax
*/
#undef FLT_MAX
#undef DBL_MAX
#undef LDBL_MAX
#define FLT_MAX		__FLT_MAX__
#define DBL_MAX		__DBL_MAX__
#define LDBL_MAX	__LDBL_MAX__

/* The difference between 1 and the least value greater than 1 that is
   representable in the given floating point type, b**1-p.  */
#undef FLT_EPSILON
#undef DBL_EPSILON
#undef LDBL_EPSILON
#define FLT_EPSILON	__FLT_EPSILON__
#define DBL_EPSILON	__DBL_EPSILON__
#define LDBL_EPSILON	__LDBL_EPSILON__

/* Minimum normalized positive floating-point number, b**(emin - 1).  */
#undef FLT_MIN
#undef DBL_MIN
#undef LDBL_MIN
#define FLT_MIN		__FLT_MIN__
#define DBL_MIN		__DBL_MIN__
#define LDBL_MIN	__LDBL_MIN__

/* Addition rounds to 0: zero, 1: nearest, 2: +inf, 3: -inf, -1: unknown.  */
/* ??? This is supposed to change with calls to fesetround in <fenv.h>.  */
#undef FLT_ROUNDS
#define FLT_ROUNDS 1

#if defined (__STDC_VERSION__) && __STDC_VERSION__ >= 199901L
/* The floating-point expression evaluation method.
        -1  indeterminate
         0  evaluate all operations and constants just to the range and
            precision of the type
         1  evaluate operations and constants of type float and double
            to the range and precision of the double type, evaluate
            long double operations and constants to the range and
            precision of the long double type
         2  evaluate all operations and constants to the range and
            precision of the long double type

   ??? This ought to change with the setting of the fp control word;
   the value provided by the compiler assumes the widest setting.  */
#undef FLT_EVAL_METHOD
#define FLT_EVAL_METHOD	__FLT_EVAL_METHOD__

/* Number of decimal digits, n, such that any floating-point number in the
   widest supported floating type with pmax radix b digits can be rounded
   to a floating-point number with n decimal digits and back again without
   change to the value,

	pmax * log10(b)			if b is a power of 10
	ceil(1 + pmax * log10(b))	otherwise
*/
#undef DECIMAL_DIG
#define DECIMAL_DIG	__DECIMAL_DIG__

#endif /* C99 */

#ifdef __STDC_WANT_DEC_FP__
/* Draft Technical Report 24732, extension for decimal floating-point
   arithmetic: Characteristic of decimal floating types <float.h>.  */

/* Number of base-FLT_RADIX digits in the significand, p.  */
#undef DEC32_MANT_DIG
#undef DEC64_MANT_DIG
#undef DEC128_MANT_DIG
#define DEC32_MANT_DIG	__DEC32_MANT_DIG__
#define DEC64_MANT_DIG	__DEC64_MANT_DIG__
#define DEC128_MANT_DIG	__DEC128_MANT_DIG__

/* Minimum exponent. */
#undef DEC32_MIN_EXP
#undef DEC64_MIN_EXP
#undef DEC128_MIN_EXP
#define DEC32_MIN_EXP	__DEC32_MIN_EXP__
#define DEC64_MIN_EXP	__DEC64_MIN_EXP__
#define DEC128_MIN_EXP	__DEC128_MIN_EXP__

/* Maximum exponent. */
#undef DEC32_MAX_EXP
#undef DEC64_MAX_EXP
#undef DEC128_MAX_EXP
#define DEC32_MAX_EXP	__DEC32_MAX_EXP__
#define DEC64_MAX_EXP	__DEC64_MAX_EXP__
#define DEC128_MAX_EXP	__DEC128_MAX_EXP__

/* Maximum representable finite decimal floating-point number
   (there are 6, 15, and 33 9s after the decimal points respectively). */
#undef DEC32_MAX
#undef DEC64_MAX
#undef DEC128_MAX
#define DEC32_MAX   __DEC32_MAX__
#define DEC64_MAX   __DEC64_MAX__
#define DEC128_MAX  __DEC128_MAX__

/* The difference between 1 and the least value greater than 1 that is
   representable in the given floating point type. */
#undef DEC32_EPSILON
#undef DEC64_EPSILON
#undef DEC128_EPSILON
#define DEC32_EPSILON	__DEC32_EPSILON__
#define DEC64_EPSILON	__DEC64_EPSILON__
#define DEC128_EPSILON	__DEC128_EPSILON__

/* Minimum normalized positive floating-point number. */
#undef DEC32_MIN
#undef DEC64_MIN
#undef DEC128_MIN
#define DEC32_MIN	__DEC32_MIN__
#define DEC64_MIN	__DEC64_MIN__
#define DEC128_MIN	__DEC128_MIN__

/* Minimum denormalized positive floating-point number. */
#undef DEC32_DEN
#undef DEC64_DEN
#undef DEC128_DEN
#define DEC32_DEN       __DEC32_DEN__
#define DEC64_DEN       __DEC64_DEN__
#define DEC128_DEN      __DEC128_DEN__

/* The floating-point expression evaluation method.
         -1  indeterminate
         0  evaluate all operations and constants just to the range and
            precision of the type
         1  evaluate operations and constants of type _Decimal32 
	    and _Decimal64 to the range and precision of the _Decimal64 
            type, evaluate _Decimal128 operations and constants to the 
	    range and precision of the _Decimal128 type;
	 2  evaluate all operations and constants to the range and
	    precision of the _Decimal128 type.  */

#undef DECFLT_EVAL_METHOD
#define DECFLT_EVAL_METHOD	__DECFLT_EVAL_METHOD__

#endif /* __STDC_WANT_DEC_FP__ */

#endif /* _FLOAT_H___ */
