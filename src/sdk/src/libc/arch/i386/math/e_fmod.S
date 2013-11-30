/*
 * Written by J.T. Conklin <jtc@netbsd.org>.
 * Public domain.
 */

.section .text

.align 4

.global fmod


fmod:
	fldl	12(%esp)
	fldl	4(%esp)
1:	fprem
	fstsw	%ax
	sahf
	jp	1b
	fstp	%st(1)
	ret

