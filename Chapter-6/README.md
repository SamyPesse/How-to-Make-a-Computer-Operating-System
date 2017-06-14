## Chapter 6: GDT

Thanks to GRUB, your kernel is no longer in real-mode, but already in [protected mode](http://en.wikipedia.org/wiki/Protected_mode), this mode allows us to use all the possibilities of the microprocessor such as virtual memory management, paging and safe multi-tasking.

#### What is the GDT?

The [GDT](http://en.wikipedia.org/wiki/Global_Descriptor_Table) ("Global Descriptor Table") is a data structure used to define the different memory areas: the base address, and the size and access privileges such as execute and write. These memory areas are called "segments".

We are going to use the GDT to define different memory segments:

* *"code"*: kernel code, used to stored the executable binary code
* *"data"*: kernel data
* *"stack"*: kernel stack, used to stored the call stack during kernel execution
* *"ucode"*: user code, used to stored the executable binary code for user program
* *"udata"*: user program data
* *"ustack"*: user stack, used to stored the call stack during execution in userland

#### How to load our GDT?

GRUB initializes a GDT but this GDT is does not correspond to our kernel.
The GDT is loaded using the LGDT assembly instruction. It expects the location of a GDT description structure:

![GDTR](./gdtr.png)

And the C structure:

```cpp
struct gdtr {
	u16 limite;
	u32 base;
} __attribute__ ((packed));
```

**Caution:** the directive ```__attribute__ ((packed))``` signal to gcc that the structure should use as little memory as possible. Without this directive, gcc include some bytes to optimize the memory alignment and the access during execution.

Now we need to define our GDT table and then load it using LGDT. The GDT table can be stored wherever we want in memory, its address should just be signaled to the process using the GDTR registry.

The GDT table is composed of segments with the following structure:

![GDTR](./gdtentry.png)

And the C structure:

```cpp
struct gdtdesc {
	u16 lim0_15;
	u16 base0_15;
	u8 base16_23;
	u8 acces;
	u8 lim16_19:4;
	u8 other:4;
	u8 base24_31;
} __attribute__ ((packed));
```

#### How to define our GDT table?

We need now to define our GDT in memory and finally load it using the GDTR registry.

We are going to store our GDT at the address:

```cpp
#define GDTBASE	0x00000800
```

The function **init_gdt_desc** in [x86.cc](https://github.com/SamyPesse/How-to-Make-a-Computer-Operating-System/blob/master/src/kernel/arch/x86/x86.cc) initialize a gdt segment descriptor.

```cpp
void init_gdt_desc(u32 base, u32 limite, u8 acces, u8 other, struct gdtdesc *desc)
{
	desc->lim0_15 = (limite & 0xffff);
	desc->base0_15 = (base & 0xffff);
	desc->base16_23 = (base & 0xff0000) >> 16;
	desc->acces = acces;
	desc->lim16_19 = (limite & 0xf0000) >> 16;
	desc->other = (other & 0xf);
	desc->base24_31 = (base & 0xff000000) >> 24;
	return;
}
```

And the function **init_gdt** initialize the GDT, some parts of the below function will be explained later and are used for multitasking.

```cpp
void init_gdt(void)
{
	default_tss.debug_flag = 0x00;
	default_tss.io_map = 0x00;
	default_tss.esp0 = 0x1FFF0;
	default_tss.ss0 = 0x18;

	/* initialize gdt segments */
	init_gdt_desc(0x0, 0x0, 0x0, 0x0, &kgdt[0]);
	init_gdt_desc(0x0, 0xFFFFF, 0x9B, 0x0D, &kgdt[1]);	/* code */
	init_gdt_desc(0x0, 0xFFFFF, 0x93, 0x0D, &kgdt[2]);	/* data */
	init_gdt_desc(0x0, 0x0, 0x97, 0x0D, &kgdt[3]);		/* stack */

	init_gdt_desc(0x0, 0xFFFFF, 0xFF, 0x0D, &kgdt[4]);	/* ucode */
	init_gdt_desc(0x0, 0xFFFFF, 0xF3, 0x0D, &kgdt[5]);	/* udata */
	init_gdt_desc(0x0, 0x0, 0xF7, 0x0D, &kgdt[6]);		/* ustack */

	init_gdt_desc((u32) & default_tss, 0x67, 0xE9, 0x00, &kgdt[7]);	/* descripteur de tss */

	/* initialize the gdtr structure */
	kgdtr.limite = GDTSIZE * 8;
	kgdtr.base = GDTBASE;

	/* copy the gdtr to its memory area */
	memcpy((char *) kgdtr.base, (char *) kgdt, kgdtr.limite);

	/* load the gdtr registry */
	asm("lgdtl (kgdtr)");

	/* initiliaz the segments */
	asm("   movw $0x10, %ax	\n \
            movw %ax, %ds	\n \
            movw %ax, %es	\n \
            movw %ax, %fs	\n \
            movw %ax, %gs	\n \
            ljmp $0x08, $next	\n \
            next:		\n");
}
```
