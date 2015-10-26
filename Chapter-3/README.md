## Chapter 3: First boot with GRUB

#### How the boot works?

When an x86-based computer is turned on, it begins a complex path to get to the stage where control is transferred to our kernel's "main" routine (`kmain()`). For this course, we are only going to consider the BIOS boot method and not it's successor (UEFI).

The BIOS boot sequence is: RAM detection -> Hardware detection/Initialization -> Boot sequence.

The most important step for us is the "Boot sequence", where the BIOS is done with its initialization and tries to transfer control to the next stage of the bootloader process.

During the "Boot sequence", the BIOS will try to determine a "boot device" (e.g. floppy disk, hard-disk, CD, USB flash memory device or network). Our Operating System will initially boot from the hard-disk (but it will be possible to boot it from a CD or a USB flash memory device in future). A device is considered bootable if the bootsector contains the valid signature bytes `0x55` and `0xAA` at offsets 511 and 512 respectively (called the magic bytes of the Master Boot Record, also known as the MBR). This signature is represented (in binary) as 0b1010101001010101. The alternating bit pattern was thought to be a protection against certain failures (drive or controller). If this pattern is garbled or 0x00, the device is not considered bootable.

BIOS physically searches for a boot device by loading the first 512 bytes from the bootsector of each device into physical memory, starting at the address `0x7C00` (1 KiB below the 32 KiB mark). When the valid signature bytes are detected, BIOS transfers control to the `0x7C00` memory address (via a jump instruction) in order to execute the bootsector code.

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

GRUB uses the Multiboot specification, the executable binary should be 32bits and must contain a special header (multiboot header) in its 8192 first bytes. Our kernel will be a ELF executable file ("Executable and Linkable Format", a common standard file format for executables in most UNIX system).

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
