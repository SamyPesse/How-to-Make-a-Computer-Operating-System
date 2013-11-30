/*
 * Written by J.T. Conklin <jtc@netbsd.org>.
 * Public domain.
 */

.section .text

.align 4

.global atan2


atan2:
	fldl	 4(%esp)
	fldl	12(%esp)
	fpatan
	ret

