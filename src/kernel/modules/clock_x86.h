
#ifndef __CLOCK__
#define __CLOCK__

#include <runtime/types.h>
#include <core/device.h>
#include <io.h>

#include <api/dev/clock.h>

class Clock_x86 : public Device
{
	public:
		Clock_x86(char* n);
		~Clock_x86();
		
		
		u32		open(u32 flag);
		u32		close();
		u32		read(u32 pos,u8* buffer,u32 size);
		u32		write(u32 pos,u8* buffer,u32 size);
		u32		ioctl(u32 id,u8* buffer);
		u32		remove();
		void	scan();
		
		void 	reset_info();
	private:
		clock_info	cinfo;
};

#endif
