
#ifndef _OS_SYSCALL_H_
#define _OS_SYSCALL_H_


int syscall0( int number );
int syscall1( int number, unsigned int p1 );
int syscall2( int number, unsigned int p1, unsigned int p2 );
int syscall3( int number, unsigned int p1, unsigned int p2, unsigned int p3 );
int syscall4( int number, unsigned int p1, unsigned int p2, unsigned int p3, unsigned int p4 );
int syscall5( int number, unsigned int p1, unsigned int p2, unsigned int p3, unsigned int p4, unsigned int p5 );

#endif
