/* setjmp function
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

.global setjmp

setjmp:
    movl 4(%esp), %edx

    /* Save return address */

    movl 0(%esp), %ecx
    movl %ecx, 0(%edx)

    /* Save registers: ebp, esp, ebx, edi and esi */

    movl %ebp, 4(%edx)
    movl %esp, 8(%edx)
    movl %ebx, 12(%edx)
    movl %edi, 16(%edx)
    movl %esi, 20(%edx)

    /* Return 0 */

    movl $0, %eax
    ret

