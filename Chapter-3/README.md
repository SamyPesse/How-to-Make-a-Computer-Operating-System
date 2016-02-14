## Chapter 3: First boot with GRUB

#### How the boot works?

When an x86-based computer is turned on, it begins a complex path to get to the stage where control is transferred to our kernel's "main" routine (`kmain()`). For this course, we are only going to consider the BIOS boot method and not it's successor (UEFI) for a 32-bit x86 machine.

The OS booting has several stages:
* The first stage is BIOS statge. When an x86 machine is powered on, the hardware is initialized with a fixed status. Specially, EIP register, which points the address of next instruction, will be filled with a fixed 32-bit value, 0x0000FFF0, CS is set as 0xFFFF0000, and CR0 register is set as 0x0. As CRO is set as 0x0, the PE bit of CR0 register is 0x0, so CPU is in 16-bit real model, which can only address 1MB memeory. In this case, 0xFFFFFFF0 (combined from CS and EIP) is an invalid address. The hardware, by default, points these address to a location of BIOS ROM, which normally stores an jump instruction to POST (Power On Self Test) routines. In conclusion, after power on, CPU will jump to the BIOS ROM to execute POST routings. POST is mainly responsible for memory check, system bus check etc. And one of import jobs of POST is to determine a 'boot device' (e.g. floppy disk, hard-disk, CD, USB, flash memory device or network). A device is considered bootable if its MBR sector (the first 512 bytes) contains the valid signature bytes '0x55' and '0xAA' at offsets 510 and 511 respectively. BIOS finds the bootable device by loading the data of MBR sector of each devices (through 'INT 0x19') into the memory starting from the address 0x7C00. If magic value '0x55AA' is found, it will let CPU jump to 0x7C00, which means CPU will execute the code stored in the MBR sector of a bootable devices. The code and data, we call bootsector, in MBR sector is written into it when we install the OS (e.g. boot/bootsect.S for Linux). Until now, every thing is done by hardware automatically, more accurately, is done by BIOS. In conclusion, in the fisrt stage, CPU will be initialized to execute BIOS routines which will find the bootable devices, which contains bootable codes. 

* The second stage is to execute the code in bootsector. Bootsector is less than 512 bytes, and has three components: 1). 446 bytes primary bootloader info; 2) 64 bytes partition table info (4 items with each 16 bytes); 3). 2-byte MBR validation check '0x55AA'. Its main purpose is to find and execute the GRUB code, or LILO code or Linux bootsec code, and then enter to the third stage. 

* In the third stage, GRUB/LILO/bootsec will load in the kernel image into the memory and uncompress it. The kernel is firstly loaded at memory address starting from 0x10000, and then moved to 0x1000 in Linux implementation. Since then on, CPU will begin to execute the code from kernel image. And enter the fourth stage of kernel initoalization including GTD, LTD, IDT and so on. 

~~The BIOS boot sequence is: RAM detection -> Hardware detection/Initialization -> Boot sequence.~~

~~The most important step for us is the "Boot sequence", where the BIOS is done with its initialization and tries to transfer control to the next stage of the bootloader process.~~

~~During the "Boot sequence", the BIOS will try to determine a "boot device" (e.g. floppy disk, hard-disk, CD, USB flash memory device or network). Our Operating System will initially boot from the hard-disk (but it will be possible to boot it from a CD or a USB flash memory device in future). A device is considered bootable if the bootsector contains the valid signature bytes `0x55` and `0xAA` at offsets 511 and 512 respectively (called the magic bytes of the Master Boot Record, also known as the MBR). This signature is represented (in binary) as 0b1010101001010101. The alternating bit pattern was thought to be a protection against certain failures (drive or controller). If this pattern is garbled or 0x00, the device is not considered bootable.~~

~~BIOS physically searches for a boot device by loading the first 512 bytes from the bootsector of each device into physical memory, starting at the address `0x7C00` (1 KiB below the 32 KiB mark). When the valid signature bytes are detected, BIOS transfers control to the `0x7C00` memory address (via a jump instruction) in order to execute the bootsector code.~~

Throughout this process the CPU has been running in 16-bit Real Mode, which is the default state for x86 CPUs in order to maintain backwards compatibility. To execute the 32-bit instructions within our kernel, a bootloader is required to switch the CPU into Protected Mode.

#### What is GRUB?

> GNU GRUB (short for GNU GRand Unified Bootloader) is a boot loader package from the GNU Project. GRUB is the reference implementation of the Free Software Foundation's Multiboot Specification, which provides a user the choice to boot one of multiple operating systems installed on a computer or select a specific kernel configuration available on a particular operating system's partitions.

To make it simple, GRUB is the first thing booted by the machine (a boot-loader) and will simplify the loading of our kernel stored on the hard-disk.

#### Why are we using GRUB?

* GRUB is very simple to use
* Make it very simple to load 32bits kernels without needs of 16bits code
* Multiboot with Linux, Windows and others
* Make it easy to load external modules in memory

#### How to use GRUB?

GRUB uses the Multiboot specification, the executable binary, the OS Image here, should be 32bits and must contain a special header (multiboot header) in its 8192 first bytes. Our kernel will be a ELF executable file ("Executable and Linkable Format", a common standard file format for executables in most UNIX system).

The first boot sequence of our kernel is written in Assembly: [start.asm](https://github.com/SamyPesse/How-to-Make-a-Computer-Operating-System/blob/master/src/kernel/arch/x86/start.asm) and we use a linker file to define our executable structure: [linker.ld](https://github.com/SamyPesse/How-to-Make-a-Computer-Operating-System/blob/master/src/kernel/arch/x86/linker.ld).

This boot process also initializes some of our C++ runtime, it will be described in the next chapter.

Multiboot header structure:

```cpp
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

You can use the command ```mbchk kernel.elf``` to validate your kernel.elf file against the multiboot standard. You can also use the command ```nm -n kernel.elf``` to validate the offset of the different objects in the ELF binary.

#### Create a disk image for our kernel and grub

The script [diskimage.sh](https://github.com/SamyPesse/How-to-Make-a-Computer-Operating-System/blob/master/src/sdk/diskimage.sh) will generate a hard disk image that can be used by QEMU.

The first step is to create a hard-disk image (c.img) using qemu-img:

```
qemu-img create c.img 2M
```

We need now to partition the disk using fdisk:

```bash
fdisk ./c.img

# Switch to Expert commands
> x

# Change number of cylinders (1-1048576)
> c
> 4

# Change number of heads (1-256, default 16):
> h
> 16

# Change number of sectors/track (1-63, default 63)
> s
> 63

# Return to main menu
> r

# Add a new partition
> n

# Choose primary partition
> p

# Choose partition number
> 1

# Choose first sector (1-4, default 1)
> 1

# Choose last sector, +cylinders or +size{K,M,G} (1-4, default 4)
> 4

# Toggle bootable flag
> a

# Choose first partition for bootable flag
> 1

# Write table to disk and exit
> w
```

We need now to attach the created partition to the loop-device using losetup. This allows a file to be access like a block device. The offset of the partition is passed as an argument and calculated using: **offset= start_sector * bytes_by_sector**.

Using ```fdisk -l -u c.img```, you get: 63 * 512 = 32256.

```bash
losetup -o 32256 /dev/loop1 ./c.img
```

We create a EXT2 filesystem on this new device using:

```bash
mke2fs /dev/loop1
```

We copy our files on a mounted disk:

```bash
mount  /dev/loop1 /mnt/
cp -R bootdisk/* /mnt/
umount /mnt/
```

Install GRUB on the disk:

```bash
grub --device-map=/dev/null << EOF
device (hd0) ./c.img
geometry (hd0) 4 16 63
root (hd0,0)
setup (hd0)
quit
EOF
```

And finally we detach the loop device:

```bash
losetup -d /dev/loop1
```

#### See Also

* [GNU GRUB on Wikipedia](http://en.wikipedia.org/wiki/GNU_GRUB)
* [Multiboot specification](https://www.gnu.org/software/grub/manual/multiboot/multiboot.html)
