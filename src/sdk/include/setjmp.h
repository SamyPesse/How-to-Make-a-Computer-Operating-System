
 

#ifndef _SETJMP_H_
#define _SETJMP_H_

typedef unsigned long jmp_buf[ 6 ];

int setjmp( jmp_buf env );
void longjmp( jmp_buf env, int val );

#endif // _SETJMP_H_
