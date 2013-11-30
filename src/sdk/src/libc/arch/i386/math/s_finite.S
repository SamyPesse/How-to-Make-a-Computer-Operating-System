/*
 * Written by Joe Keane <jgk@jgk.org>.
 */

.section .text

.align 4

.global finite


finite:
	movl	8(%esp),%eax
	movl    $0xFFEFFFFF,%ecx
	subl    %eax,%ecx
	xorl    %ecx,%eax
	shrl	$31, %eax
	ret

