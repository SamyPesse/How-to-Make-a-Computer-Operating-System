
#ifndef __IDE__
#define __IDE__

#include <runtime/types.h>
#include <core/device.h>
#include <io.h>

class Ide : public Device
{
	public:
		Ide(char* n);
		~Ide();
		
		
		u32		open(u32 flag);
		u32		close();
		u32		read(u32 pos,u8* buffer,u32 size);
		u32		write(u32 pos,u8* buffer,u32 size);
		u32		ioctl(u32 id,u8* buffer);
		u32		remove();
		void	scan();
		
		void	setId(u32 flag);
		
	private:
		u32 id;

};

#endif
