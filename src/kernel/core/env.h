#ifndef ENV_H
#define ENV_H

#include <core/file.h>
#include <runtime/list.h>


class Variable : public File
{
	public:
		Variable(char* n,char* v);
		~Variable();
		
		u32		open(u32 flag);
		u32		close();
		u32		read(u32 pos,u8* buffer,u32 size);
		u32		write(u32 pos,u8* buffer,u32 size);
		u32		ioctl(u32 id,u8* buffer);
		u32		remove();
		void	scan();
		
		
		
		
	protected:
		char*	value;


};

#endif