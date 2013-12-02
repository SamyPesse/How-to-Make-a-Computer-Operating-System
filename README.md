How to Make a Computer Operating System
=======================================

**Caution**: This repository is a remake of my old course. It was written several years ago [as one of my first projects when I was in High School](https://github.com/SamyPesse/devos) so it's normal if some parts of the code look like "crap". The original course was in French and I'm not an English native. I'm going to continue and improve this course in my free-time.

**Source Code**: All the system source code will be stored in the `src` directory. Each step will contain links to the different related files.

**Contributions**: This course is open to contributions, feel free to signal errors with issues or directly correct the errors with pull-requests.

**Questions**: Feel free to ask any questions by adding issues. Please don't email me.

You can follow me on Twitter [@SamyPesse](https://twitter.com/SamyPesse) or support me on [Flattr](https://flattr.com/profile/samy.pesse) or [Gittip](https://www.gittip.com/SamyPesse/).

### What kind of OS are we building?

The goal is to build a very simple UNIX-based operating system in C++, not just a "proof-of-concept". The OS should be able to boot, start an userland shell and be extensible.

[![Screen](https://raw.github.com/SamyPesse/How-to-Make-a-Computer-Operating-System/master/preview.png)](https://raw.github.com/SamyPesse/How-to-Make-a-Computer-Operating-System/master/preview.png)

### Summary

#### [Chapter 1: Introduction about the x86 architecture and about our OS](Chapter-1/README.md)

#### [Chapter 2: Setup the development environment](Chapter-2/README.md)

#### [Chapter 3: First boot with GRUB](Chapter-3/README.md)

#### [Chapter 4: Backbone of the OS and C++ runtime](Chapter-4/README.md)

#### [Chapter 5: Base classes for managing x86 architecture](Chapter-5/README.md)

#### [Chapter 6: GDT](Chapter-6/README.md)

#### Chapter 7: IDT and interruptions

#### Chapter 8: Memory management: physical and virtual

#### Chapter 9: Process management and multitasking

#### Chapter 10: External program execution: ELF files

#### Chapter 11: Userland and syscalls

#### Chapter 12: Modular drivers

#### Chapter 13: Some basics modules: console, keyboard

#### Chapter 14: IDE Hard disks

#### Chapter 15: DOS Partitions

#### Chapter 16: EXT2 read-only filesystems

#### Chapter 17: Standard C library (libC)

#### Chapter 18: UNIX basic tools: sh, cat

#### Chapter 19: Lua interpreter

