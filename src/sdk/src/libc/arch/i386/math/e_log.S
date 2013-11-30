/*
 * Written by J.T. Conklin <jtc@netbsd.org>.
 * Public domain.
 *
 * Changed to use fyl2xp1 for values near 1, <drepper@cygnus.com>.
 */

.section .rodata

.align 4


one:
    .double 1.0


/* It is not important that this constant is precise.  It is only
   a value which is known to be on the safe side for using the
   fyl2xp1 instruction.  */


limit:
    .double 0.29



#ifdef PIC
#define MO(op) op##@GOTOFF(%edx)
#else
#define MO(op) op
#endif

.section .text

.global log


log:
	fldln2			// log(2)
	fldl	4(%esp)		// x : log(2)
	fxam
	fnstsw
#ifdef PIC
	LOAD_PIC_REG (dx)
#endif
	fld	%st		// x : x : log(2)
	sahf
	jc	3f		// in case x is NaN or +-Inf
4:	fsubl	MO(one)		// x-1 : x : log(2)
	fld	%st		// x-1 : x-1 : x : log(2)
	fabs			// |x-1| : x-1 : x : log(2)
	fcompl	MO(limit)	// x-1 : x : log(2)
	fnstsw			// x-1 : x : log(2)
	andb	$0x45, %ah
	jz	2f
	fstp	%st(1)		// x-1 : log(2)
	fyl2xp1			// log(x)
	ret

2:	fstp	%st(0)		// x : log(2)
	fyl2x			// log(x)
	ret

3:	jp	4b		// in case x is +-Inf
	fstp	%st(1)
	fstp	%st(1)
	ret

