/*
 * Written by J.T. Conklin <jtc@netbsd.org>.
 * Public domain.
 */

.section .text

.align 4

.global cos


cos:
	fldl	4(%esp)
	fcos
	fnstsw	%ax
	testl	$0x400,%eax
	jnz	1f
	ret

.align 4

1:	fldpi
	fadd	%st(0)
	fxch	%st(1)
2:	fprem1
	fnstsw	%ax
	testl	$0x400,%eax
	jnz	2b
	fstp	%st(1)
	fcos
	ret

