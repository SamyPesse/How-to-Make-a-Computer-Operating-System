How to Make a Computer Operating System
=======================================

**Caution**: This repository is a remake of my old course. It was written several years ago [as one of my first projects when I was in High School](https://github.com/SamyPesse/devos) so it's normal if some parts of the code looks like "crap". The original course was in French and I'm not an English native.

**Source Code**: All the system source code will be stored in the `src` directory. Each steps of the course will be linked to a git tag.

**Contributions**: This course is open to contribution, feel free to signal errors with issues or directly correct the errors with pull-requests.

**Questions**: Feel free to ask the questions by adding issues and please don't email me.

### What kind of OS are we building?

The goal is to build a very simple UNIX-based operating system in C++, but the goal is not to just build a "proof-of-concept". The OS should be able to boot, start an userland shell and be extensible.

[![Screen](https://raw.github.com/SamyPesse/How-to-Make-a-Computer-Operating-System/master/preview.png)](https://raw.github.com/SamyPesse/How-to-Make-a-Computer-Operating-System/master/preview.png)

### Summary

#### [Chapter 1: Introduction about the x86 architecture and about our OS](Chapter-1/README.md)

#### [Chapter 2: Setup the development environment](Chapter-2/README.md)

#### [Chapter 3: First boot with GRUB](Chapter-3/README.md)

#### Chapter 4: Backbone of the OS and C++ runtime

#### Chapter 5: Base classes for managing x86 architecture

#### Chapter 6: GDT and IDT

#### Chapter 7: Memory management: physical and virtual

#### Chapter 8: Process management and multitasking

#### Chapter 9: External program execution: ELF files

#### Chapter 10: Userland and syscalls

#### Chapter 11: Modular drivers

#### Chapter 12: Some basics modules: console, keyboard

#### Chapter 13: IDE Hard disks

#### Chapter 14: DOS Partitions

#### Chapter 15: EXT2 read-only filesystems

#### Chapter 16: Standard C library (libC)

#### Chapter 17: UNIX basic tools: sh, cat

#### Chapter 18: Lua interpreter

