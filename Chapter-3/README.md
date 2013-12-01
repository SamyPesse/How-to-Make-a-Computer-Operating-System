## Chapter 3: First boot with GRUB

#### How the boot works?

When an x86-based computer is turned on, it begins a complex path to get to the stage where control is transferred to our kernel's "main" routine ("kmain()"). For this course, we are not going to consider new UEFI method but only BIOS boot method.

The BIOS boot sequence is: RAM detection -> Hardware detection/Initialization -> Boot sequence.

The step important for us is the "Boot sequence", when the BIOS is done with its initialization and tries to transfer control to the next stage of the bootloader process.

During the "Boot sequence", the BIOS will first choose the "boot device" (floopy disk, hard-disk, CD, usb flash memory device or network). Our Operating system will first boot from the hard-disk (but it's possible to boot it from a CD or a usb flash memory device).

The BIOS will read the 512 bytes from the first valid bootsector (If the last two bytes are 0x55, and then 0xAA, then the BIOS considers this to be a valid bootsector), If the BIOS never finds a valid bootsector, it will lock up with an error message. And it'll transfer these 512 bytes into physical memory starting at address 0x7c00 then starts running the code that now begins at 0x7c00.

When the BIOS transfers control to the bootsector, the bootsector code is loaded and running at physical address 0x7c00 and the CPU is in 16-bit Real Mode but our kernel will be only 32bits so we need a bootloader to read our kernel switch to protected mode and starts running it.

#### What is GRUB?

> GNU GRUB (short for GNU GRand Unified Bootloader) is a boot loader package from the GNU Project. GRUB is the reference implementation of the Free Software Foundation's Multiboot Specification, which provides a user the choice to boot one of multiple operating systems installed on a computer or select a specific kernel configuration available on a particular operating system's partitions.

To make it simple, GRUB is the first thing booted by the machine (a boot-loader) and will simplify the loading of our kernel stored on the hard-disk.

#### Why are we using GRUB?

* GRUB is very simple to use
* Make it very simple to load 32bits kernels without needs of 16bits code
* Multiboot with Linux, Windows and others
* Make it easy to laod external modules in memory

#### How to use GRUB?

GRUB use the Multiboot specification, the executable binary should be 32bits and must contains a special header (multiboot header) in its 8192 first bytes. Our kernel will be a ELF executable file ("Executable and Linkable Format", it is a common standard file format for executables in most UNIX system).

The first boot sequence of our kernel is written in Assembly: [start.asm](https://github.com/SamyPesse/How-to-Make-a-Computer-Operating-System/blob/master/src/kernel/arch/x86/start.asm) and we use a linker file to define our executable structure: [linker.ld](https://github.com/SamyPesse/How-to-Make-a-Computer-Operating-System/blob/master/src/kernel/arch/x86/linker.ld).

This boot process alse initialize some of our C++ runtime, it will be described in the next chapter.

Multiboot header structure:

```
struct multiboot_info {
	u32 flags;
	u32 low_mem;
	u32 high_mem;
	u32 boot_device;
	u32 cmdline;
	u32 mods_count;
	u32 mods_addr;
	struct {
		u32 num;
		u32 size;
		u32 addr;
		u32 shndx;
	} elf_sec;
	unsigned long mmap_length;
	unsigned long mmap_addr;
	unsigned long drives_length;
	unsigned long drives_addr;
	unsigned long config_table;
	unsigned long boot_loader_name;
	unsigned long apm_table;
	unsigned long vbe_control_info;
	unsigned long vbe_mode_info;
	unsigned long vbe_mode;
	unsigned long vbe_interface_seg;
	unsigned long vbe_interface_off;
	unsigned long vbe_interface_len;
};
```

#### See Also

* [GNU GRUB on wikipedia](http://en.wikipedia.org/wiki/GNU_GRUB)
* [Multiboot specification](https://www.gnu.org/software/grub/manual/multiboot/multiboot.html)
