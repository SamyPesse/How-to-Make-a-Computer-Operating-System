/* longjmp function
 *
 * Copyright (c) 2009 Zoltan Kovacs
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of version 2 of the GNU General Public License
 * as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 */

.section .text

.global longjmp

longjmp:
    movl 4(%esp), %edx
    movl 8(%esp), %eax

    /* Restore registers */

    movl 4(%edx), %ebp
    movl 8(%edx), %esp
    movl 12(%edx), %ebx
    movl 16(%edx), %edi
    movl 20(%edx), %esi

    /* Restore return address */

    movl 0(%edx), %ecx
    movl %ecx, 0(%esp)

    /* Check return code */

    cmpl $0, %eax
    je  1f
    ret

1:
    movl $1, %eax
    ret

