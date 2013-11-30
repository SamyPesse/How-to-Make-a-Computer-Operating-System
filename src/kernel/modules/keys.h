
#ifndef __KEYS__
#define __KEYS__

#include <runtime/types.h>
#include <core/device.h>
#include <io.h>

#include <api/dev/keyboard.h>

class Keyboard : public Device
{
	public:
		Keyboard(char* n);
		~Keyboard();
		
		
		u32		open(u32 flag);
		u32		close();
		u32		read(u32 pos,u8* buffer,u32 size);
		u32		write(u32 pos,u8* buffer,u32 size);
		u32		ioctl(u32 id,u8* buffer);
		u32		remove();
		void	scan();
		
	private:
		char	scantable[TABLE_KEYBOARD_SIZE];
};

#endif
