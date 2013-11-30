
#ifndef __CONSOLE__
#define __CONSOLE__

#include <runtime/types.h>
#include <core/file.h>
#include <io.h>

#include <api/dev/ioctl.h>
#include <api/dev/tty.h>

class Console : public Device
{
	public:
		Console(char* n,u32 flag);
		~Console();
		
		
		u32		open(u32 flag);
		u32		close();
		u32		read(u32 pos,u8* buffer,u32 size);
		u32		write(u32 pos,u8* buffer,u32 size);
		u32		ioctl(u32 id,u8* buffer);
		u32		remove();
		void	scan();
		
		void	reset_info();
		
	private:
		tty_info_static	sinfo;
		tty_info_moving	minfo;
	
		Io*		iotty;
};

#endif
