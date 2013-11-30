CP       = cp
RM       = rm
MKDIR    = mkdir
TRUE     = true

CC       = gcc
CXX      = g++
AS       = nasm
LD       = ld
AR       = ar
RANLIB   = ranlib
STRIP    = strip

INCDIR   = $(SDKDIR)/include
LIBDIR   = $(SDKDIR)/lib

DEFS:= $(DEFS)

CFLAGS   = -I $(INCDIR) -Wall -fno-builtin -g -O2 -w -trigraphs   -fno-exceptions -fno-stack-protector -O0 -m32  -fno-rtti $(DEFS)
CXXFLAGS = $(CFLAGS) 
ASFLAGS  = $(CFLAGS) 

ifeq ($(CRT_FILE),)
CRT_FILE = crt_c.o
endif

LDFLAGS  = -melf_i386 -L $(INCDIR)  -T ./linker.ld --entry=_start -nostdlib -L $(LIBDIR) -lc $(LIBS)
MYOS_VERSION=500


all: $(TARGET)

$(TARGET): $(OBJS)
	$(LD) -o $@ $^ $(SDKDIR)/lib/$(CRT_FILE) $(LDFLAGS)
	cp $(TARGET) $(SDKDIR)/bootdisk/bin/$(TARGET)

install:
	cp $(TARGET) $(SDKDIR)/bootdisk/bin/$(TARGET)

run:
	cd $(SDKDIR) &&	sh ./diskimage.sh
	cd $(SDKDIR) &&	sh ./qemu.sh

%.o: %.c
	$(CC) $(CFLAGS)  -c $< 

%.o: %.cpp
	$(CXX) $(CXXFLAGS)  -c $< 
	
%.o: %.cc
	$(CXX) $(CXXFLAGS)  -c $< 
	
.PHONY: clean 
	
clean:
	rm -rf *.o $(TARGET)

