#ifndef __X86__
#define __X86__

#include <runtime/types.h>

#define IDTSIZE		0xFF	/* nombre max. de descripteurs dans la table */
#define GDTSIZE		0xFF	/* nombre max. de descripteurs dans la table */

#define IDTBASE		0x00000000	/* addr. physique ou doit resider la IDT */
#define GDTBASE		0x00000800	/* addr. physique ou doit resider la gdt */

#define INTGATE  0x8E00		/* utilise pour gerer les interruptions */
#define TRAPGATE 0xEF00		/* utilise pour faire des appels systemes */

#define	KERN_PDIR			0x00001000
#define	KERN_STACK			0x0009FFF0
#define	KERN_BASE			0x00100000
#define KERN_PG_HEAP		0x00800000
#define KERN_PG_HEAP_LIM	0x10000000
#define KERN_HEAP			0x10000000
#define KERN_HEAP_LIM		0x40000000

#define	USER_OFFSET 		0x40000000
#define	USER_STACK 			0xE0000000
	
#define KERN_PG_1			0x400000
#define KERN_PG_1_LIM 		0x800000

#define	VADDR_PD_OFFSET(addr)	((addr) & 0xFFC00000) >> 22
#define	VADDR_PT_OFFSET(addr)	((addr) & 0x003FF000) >> 12
#define	VADDR_PG_OFFSET(addr)	(addr) & 0x00000FFF
#define PAGE(addr)		(addr) >> 12

#define	PAGING_FLAG 		0x80000000	/* CR0 - bit 31 */
#define PSE_FLAG			0x00000010	/* CR4 - bit 4  */

#define PG_PRESENT			0x00000001	/* page directory / table */
#define PG_WRITE			0x00000002
#define PG_USER				0x00000004
#define PG_4MB				0x00000080

#define	PAGESIZE 			4096
#define	RAM_MAXSIZE			0x100000000
#define	RAM_MAXPAGE			0x100000

/* Descripteur de segment */
struct gdtdesc {
	u16 lim0_15;
	u16 base0_15;
	u8 base16_23;
	u8 acces;
	u8 lim16_19:4;
	u8 other:4;
	u8 base24_31;
} __attribute__ ((packed));

/* Registre GDTR */
struct gdtr {
	u16 limite;
	u32 base;
} __attribute__ ((packed));

struct tss {
	u16 previous_task, __previous_task_unused;
	u32 esp0;
	u16 ss0, __ss0_unused;
	u32 esp1;
	u16 ss1, __ss1_unused;
	u32 esp2;
	u16 ss2, __ss2_unused;
	u32 cr3;
	u32 eip, eflags, eax, ecx, edx, ebx, esp, ebp, esi, edi;
	u16 es, __es_unused;
	u16 cs, __cs_unused;
	u16 ss, __ss_unused;
	u16 ds, __ds_unused;
	u16 fs, __fs_unused;
	u16 gs, __gs_unused;
	u16 ldt_selector, __ldt_sel_unused;
	u16 debug_flag, io_map;
} __attribute__ ((packed));

/* Descripteur de segment */
struct idtdesc {
	u16 offset0_15;
	u16 select;
	u16 type;
	u16 offset16_31;
} __attribute__ ((packed));

/* Registre IDTR */
struct idtr {
	u16 limite;
	u32 base;
} __attribute__ ((packed));

typedef struct
{
	u32 edi, esi, ebp, esp, ebx, edx, ecx, eax;
	u32 ds, es, fs, gs;
	u32 which_int, err_code;
	u32 eip, cs, eflags, user_esp, user_ss;
} __attribute__((packed)) regs_t;

typedef void (*int_desc)(void);

extern "C" {
	void init_gdt_desc(u32, u32, u8, u8, struct gdtdesc *);
	void init_gdt(void);
	void init_idt_desc(u16, u32, u16, struct idtdesc *);
	void init_idt(void);
	void init_pic(void);
	int install_irq(unsigned int num,unsigned int irq);
	void switch_to_task(process_st* current, int mode);
	extern tss 		default_tss;
	u32 cpu_vendor_name(char *name);
	int dequeue_signal(int);
	int handle_signal(int);
}

#endif
