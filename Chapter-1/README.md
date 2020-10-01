## Chapter 1: Introduction to the x86 architecture and about our OS

### What is the x86 architecture?

> The term x86 denotes a family of backward compatible instruction set architectures based on the Intel 8086 CPU.

The x86 architecture is the most common instruction set architecture. It was introduced in 1981 for the IBM PC. A large amount of software, including operating systems (OS's) such as DOS, Windows, Linux, BSD, Solaris and Mac OS X, function with x86-based hardware.

In this course we are not going to design an operating system for the x86-64 architecture but for x86-32, thanks to backward compatibility, our OS will be compatible with our newer PCs (but be cautious if you test it on your real machine).

### Our Operating System

The goal is to build a very simple UNIX-based operating system in C++. The goal is not to just build a "proof-of-concept", the OS should also be able to boot, start a userland shell and be extensible.

The OS will be built for the x86 architecture, running on 32 bits, and compatible with IBM PCs.

**Specifications:**

* Code in C++
* x86, 32 bit architecture
* Boot with Grub
* Kind of modular system for drivers
* Kind of UNIX style
* Multitasking
* ELF executable in userland
* Modules (accessible in userland using /dev/...) :
    * IDE disks
    * DOS partitions
    * Clock
    * EXT2 (read only)
    * Boch VBE
* Userland :
    * API Posix
    * LibC
    * "Can" run a shell or some executables (e.g., lua)
