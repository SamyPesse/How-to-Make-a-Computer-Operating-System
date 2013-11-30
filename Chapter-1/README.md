## Chapter 1: Introduction about the x86 architecture and about our OS

### What is the x86 architecture?

> The term x86 denotes a family of backward compatible instruction set architectures based on the Intel 8086 CPU.

The x86 arhictacture is most common instruction set architecture since the introduction in 1981 of the IBM PC. A large amount of software, including operating systems (OSs) such as DOS, Windows, Linux, BSD, Solaris and Mac OS X, functions with x86-based hardware.

In this course we are not going to design an operating system for x86-64 architecture but for x86-32, thanks to backward compatibility, our OS will be compatible with our PCs (but take caution if you want to test it on your real machine).

### Our Operating System

The goal is to build a very simple UNIX-based operating system in C++, but the goal is not to just build a "proof-of-concept". The OS should be able to boot, start an userland shell and be extensible.

The OS will be built for x86 32bits architecture and IBM compatible PCs.

**Specifications:**

* Code in C++
* x86-32 architecture
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
    * "Can" run a shell or some excutables like Lua, ...

