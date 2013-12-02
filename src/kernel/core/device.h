#ifndef DEVICE_H
#define DEVICE_H

#include <core/file.h>
#include <runtime/list.h>


class Device : public File
{
	public:
		Device(char* n);
		~Device();
		
		virtual u32		open(u32 flag);
		virtual u32		close();
		virtual u32		read(u8* buffer,u32 size);
		virtual u32		write(u8* buffer,u32 size);
		virtual u32		ioctl(u32 id,u8* buffer);
		virtual u32		remove();
		virtual void	scan();
		
		
	protected:

};

#endif