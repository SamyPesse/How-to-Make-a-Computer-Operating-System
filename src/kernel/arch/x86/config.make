LDFLAG= -melf_i386 -static  -L ./  -T ./arch/$(ARCH)/linker.ld
SC=g++
FLAG= $(INCDIR) -g -O2 -w -trigraphs -fno-builtin  -fno-exceptions -fno-stack-protector -O0 -m32  -fno-rtti -nostdlib -nodefaultlibs 
ASM=nasm  
ASMFLAG=-f elf -o
LD=ld
NM=nm
OBJDUMP=objdump
