.section .text

.align 4

.global fabs


fabs:
	fldl	4(%esp)
	fabs
	ret

