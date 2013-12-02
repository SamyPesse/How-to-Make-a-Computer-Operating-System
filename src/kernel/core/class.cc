#include <os.h>

/*
Static objects
*/

Io 				io;			/* Input/Output interface */
Architecture 	arch;		/*	Cpu and architecture interface */
Vmm 			vmm;		/*	Virtual memory manager interface */
Filesystem		fsm;		/*	Filesystem interface */
Module			modm;		/* Module manager */
Syscalls		syscall;	/* Syscalls manager */
System			sys;		/* System manager */
