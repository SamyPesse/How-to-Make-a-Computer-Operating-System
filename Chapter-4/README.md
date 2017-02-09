## Chapter 4: Backbone of the OS and C++ runtime

#### C++ kernel run-time

A kernel can be written in C++ just as it can be in C, with the exception of a few pitfalls that come with using C++ (runtime support, constructors, etc). 

The compiler will assume that all the necessary C++ runtime support is available by default, but as we are not linking libsupc++ into your C++ kernel, we need to add some basic functions that can be found in the [cxx.cc](https://github.com/SamyPesse/How-to-Make-a-Computer-Operating-System/blob/master/src/kernel/runtime/cxx.cc) file.

**Caution:** The operators `new` and `delete` cannot be used before virtual memory and pagination have been initialized.

#### Basic C/C++ functions

The kernel code can't use functions from the standard libraries so we need to add some basic functions for managing memory and strings:

```cpp
void 	itoa(char *buf, unsigned long int n, int base);

void *	memset(char *dst,char src, int n);
void *	memcpy(char *dst, char *src, int n);

int 	strlen(char *s);
int 	strcmp(const char *dst, char *src);
int 	strcpy(char *dst,const char *src);
void 	strcat(void *dest,const void *src);
char *	strncpy(char *destString, const char *sourceString,int maxLength);
int 	strncmp( const char* s1, const char* s2, int c );
```

These functions are defined in [string.cc](https://github.com/SamyPesse/How-to-Make-a-Computer-Operating-System/blob/master/src/kernel/runtime/string.cc), [memory.cc](https://github.com/SamyPesse/How-to-Make-a-Computer-Operating-System/blob/master/src/kernel/runtime/memory.cc), [itoa.cc](https://github.com/SamyPesse/How-to-Make-a-Computer-Operating-System/blob/master/src/kernel/runtime/itoa.cc)

#### C types

In the next step, we're going to define different types we're going to use in our code. Most of our variable types are going to be unsigned. This means that all the bits are used to store the integer. Signed variables use their first bit to indicate their sign. 

```cpp
typedef unsigned char 	u8;
typedef unsigned short 	u16;
typedef unsigned int 	u32;
typedef unsigned long long 	u64;

typedef signed char 	s8;
typedef signed short 	s16;
typedef signed int 		s32;
typedef signed long long	s64;
```

#### Compile our kernel

Compiling a kernel is not the same thing as compiling a linux executable, we can't use a standard library and should have no dependencies to the system.

Our [Makefile](https://github.com/SamyPesse/How-to-Make-a-Computer-Operating-System/blob/master/src/kernel/Makefile) will define the process to compile and link our kernel.

For x86 architecture, the followings arguments will be used for gcc/g++/ld:

```
# Linker
LD=ld
LDFLAG= -melf_i386 -static  -L ./  -T ./arch/$(ARCH)/linker.ld

# C++ compiler
SC=g++
FLAG= $(INCDIR) -g -O2 -w -trigraphs -fno-builtin  -fno-exceptions -fno-stack-protector -O0 -m32  -fno-rtti -nostdlib -nodefaultlibs 

# Assembly compiler
ASM=nasm
ASMFLAG=-f elf -o
```
