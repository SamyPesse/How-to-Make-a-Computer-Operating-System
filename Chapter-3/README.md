## Chapter 3: First boot with GRUB

#### How the boot works?

When an x86-based computer is turned on, it begins a complex path to get to the stage where control is transferred to our kernel's "main" routine ("kmain()"). For this course, we are not going to consider new UEFI method but only BIOS boot method.

The BIOS boot sequence is: RAM detection -> Hardware detection/Initialization -> Boot sequence.

The step important for us is the "Boot sequence", when the BIOS is done with its initialization and tries to transfer control to the next stage of the bootloader process.

During the "Boot sequence", the BIOS will first choose the "boot device" (floopy disk, hard-disk, CD, usb flash memory device or network). Our Operating system will first boot from the hard-disk (but it's possible to boot it from a CD or a usb flash memory device).

The BIOS will read the 512 bytes from the first valid bootsector (If the last two bytes are 0x55, and then 0xAA, then the BIOS considers this to be a valid bootsector), If the BIOS never finds a valid bootsector, it will lock up with an error message. And it'll transfer these 512 bytes into physical memory starting at address 0x7c00 then starts running the code that now begins at 0x7c00.

#### What is GRUB?

> GNU GRUB (short for GNU GRand Unified Bootloader) is a boot loader package from the GNU Project. GRUB is the reference implementation of the Free Software Foundation's Multiboot Specification, which provides a user the choice to boot one of multiple operating systems installed on a computer or select a specific kernel configuration available on a particular operating system's partitions.

To make it simple, Grub is the first thing booted by the machine (a boot-loader) and will simplify the loading of our kernel stored on the hard-disk.

#### Why are we using Grub?
