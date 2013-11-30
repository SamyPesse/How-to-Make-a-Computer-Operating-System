
#ifndef __X86Serial__
#define __X86Serial__

#include <runtime/types.h>
#include <core/device.h>
#include <io.h>

#define COM1	   0x3F8	
#define IRQ_COM1   4
#define COM2 	   2F8 	
#define IRQ_COM2   3
#define COM3 	   3E8 	
#define IRQ_COM3   4
#define COM4 	   2E8 	
#define IRQ_COM4   3


class X86Serial : public Device
{
	public:
		X86Serial(char* n);
		~X86Serial();
		
		void	putc(char c);
		char 	getc();
		
		u32		open(u32 flag);
		u32		close();
		u32		read(u32 pos,u8* buffer,u32 size);
		u32		write(u32 pos,u8* buffer,u32 size);
		u32		ioctl(u32 id,u8* buffer);
		u32		remove();
		void	scan();
		
	private:
		static u8 init_serial;
};

#endif
