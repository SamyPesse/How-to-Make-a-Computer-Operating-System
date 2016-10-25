## Chapter 1: Introduction to the x86 architecture and about our OS

### What is the x86 architecture?

> The term x86 denotes a family of backward compatible instruction set architectures based on the Intel 8086 CPU.

Since its introduction in 1981 for the IBM PC, x86 has become the most common instruction set architecture. A large amount of software, including operating systems (OS), function with x86-based hardware. Examples of these include DOS, Windows, Linux, BSD, Solaris and macOS.

In this course, we are not going to design an operating system for the x86/64 architecture, but for x86-32. Thanks to backward compatibility, our OS will be compatible with newer PCs (but take caution if you want to test it on your real machine).

### Our Operating System

The goal is to build a very simple UNIX-based operating system in C++. However, the goal is not to just build a "proof-of-concept". The OS should be able to boot, start a userland shell and be extensible.

To clarify, the OS will be built for the x86 architecture, running as 32-bit, and should be compatible with IBM PCs.

**Specifications:**

* Coded in C++
* x86 and 32 bit architecture
* Boot with GRUB
* Kind of modular system for drivers
* Kind of UNIX style
* Multitasking possible
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
