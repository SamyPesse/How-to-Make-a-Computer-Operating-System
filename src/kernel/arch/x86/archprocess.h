
#ifndef APROC_H
#define APROC_H

#include <runtime/types.h>

extern "C" {

#define KERNELMODE	0
#define USERMODE	1

	/** info processor structure for a process */
	struct process_st {
		int pid;

		struct {
			u32 eax, ecx, edx, ebx;
			u32 esp, ebp, esi, edi;
			u32 eip, eflags;
			u32 cs:16, ss:16, ds:16, es:16, fs:16, gs:16;
			u32 cr3;
		} regs __attribute__ ((packed));

		struct {
			u32 esp0;
			u16 ss0;
		} kstack __attribute__ ((packed));

		/* 
		 * ATTENTION ! On ne peut ajouter des elements au dessus de cette
		 * limite sans modifier la fonction assembleur do_switch() qui effectue
		 * la commutation de tache.
		 */

		/* NOTE: redondance entre regs.cr3 et pd->base->p_addr */
		struct page_directory *pd;	

		list_head pglist;	/* Pages utilisees par le processus (exec, data, stack) */

		char *b_exec;
		char *e_exec;
		char *b_bss;
		char *e_bss;
		char *b_heap;
		char *e_heap;			/* Pointe sur le sommet du "heap" */

		u32 signal;
		void* sigfn[32];

		void*	vinfo;
		
	} __attribute__ ((packed));
}

#endif
