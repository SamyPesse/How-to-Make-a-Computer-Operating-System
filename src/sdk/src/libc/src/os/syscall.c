
 

#include <os.h>


int syscall0( int number ){
	int ret;
	asm volatile ("		   \
		mov %1, %%eax	\n \
		int $0x80		\n \
		mov %%eax, %0" 
		: "=g" (ret) 
		: "g" (number)
	);
	return ret;
}


int syscall1( int number, uint32_t p1 ){
	int ret;
	asm volatile ("		   \
		mov %1, %%eax	\n \
		mov %2, %%ebx	\n \
		int $0x80		\n \
		mov %%eax, %0" 
		: "=g" (ret) 
		: "g" (number), "g" (p1)
	);
	return ret;
}


int syscall2( int number, uint32_t p1, uint32_t p2 ){
	int ret;

	asm volatile ("		   \
		mov %1, %%eax	\n \
		mov %2, %%ebx	\n \
		mov %3, %%ecx	\n \
		int $0x80	\n \
		mov %%eax, %0"	
		: "=g" (ret) 
		: "g" (number), "g" (p1), "g" (p2)
	);
	return ret;
}


int syscall3( int number, uint32_t p1, uint32_t p2, uint32_t p3 ){
	int ret;
	asm volatile ("			   \
		mov %1, %%eax		\n \
		mov %2, %%ebx		\n \
		mov %3, %%ecx		\n \
		mov %4, %%edx		\n \
		int $0x80		\n \
		mov %%eax, %0" 
		: "=g" (ret) 
		: "g" (number),"g" (p1), "g" (p2),  "g" (p3)
	);
	return ret;
}


int syscall4( int number, uint32_t p1, uint32_t p2, uint32_t p3, uint32_t p4 ){
	int ret;
	asm volatile ("			   \
		mov %1, %%eax		\n \
		mov %2, %%ebx		\n \
		mov %3, %%ecx		\n \
		mov %4, %%edx		\n \
		mov %5, %%edi		\n \
		int $0x80		\n \
		mov %%eax, %0" 
		: "=g" (ret) 
		: "g" (number),"g" (p1), "g" (p2),  "g" (p3),  "g" (p4)
	);
	return ret;
}


int syscall5( int number, uint32_t p1, uint32_t p2, uint32_t p3, uint32_t p4, uint32_t p5 ){
	int ret;
	asm volatile ("			   \
		mov %1, %%eax		\n \
		mov %2, %%ebx		\n \
		mov %3, %%ecx		\n \
		mov %4, %%edx		\n \
		mov %5, %%edi		\n \
		mov %6, %%esi		\n \
		int $0x80		\n \
		mov %%eax, %0" 
		: "=g" (ret) 
		: "g" (number),"g" (p1), "g" (p2),  "g" (p3),  "g" (p4),  "g" (p5)
	);
	return ret;
}


