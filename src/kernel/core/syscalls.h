
#ifndef SYSCALL_H
#define SYSCALL_H

#include <core/file.h>
#include <runtime/list.h>


#define NB_SYSCALLS	100


typedef void (*syscall_handler)(void);

class Syscalls 
{
	public:
		void	init();
		void	add(u32 num,syscall_handler h);
		void	call(u32 num);
		
	protected:
		syscall_handler		calls[NB_SYSCALLS];

};

extern Syscalls	syscall;

#endif
