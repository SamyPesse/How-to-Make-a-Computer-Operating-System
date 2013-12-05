
#ifndef MODLINK_H
#define MODLINK_H

#include <core/file.h>
#include <runtime/list.h>


class ModLink : public File
{
	public:
		ModLink(char* n);
		~ModLink();

		u32		open(u32 flag);
		u32		close();
		u32		read(u8* buffer,u32 size);
		u32		write(u8* buffer,u32 size);
		u32		ioctl(u32 id,u8* buffer);
		u32		remove();
		void	scan();




	protected:

};

#endif
