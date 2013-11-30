
#ifndef __NULL__
#define __NULL__

#include <runtime/types.h>
#include <core/device.h>
#include <io.h>

class Null : public Device
{
	public:
		Null(char* n);
		~Null();
		
		
		u32		open(u32 flag);
		u32		close();
		u32		read(u32 pos,u8* buffer,u32 size);
		u32		write(u32 pos,u8* buffer,u32 size);
		u32		ioctl(u32 id,u8* buffer);
		u32		remove();
		void	scan();
};

#endif
