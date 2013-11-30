
#ifndef USER_H
#define USER_H

#include <core/file.h>
#include <runtime/list.h>


enum {
	USER_ROOT,	//root
	USER_NORM	//utilisateur normal
};

class User : public File
{
	public:
		User(char* n);
		~User();
		
		u32		open(u32 flag);
		u32		close();
		u32		read(u8* buffer,u32 size);
		u32		write(u8* buffer,u32 size);
		u32		ioctl(u32 id,u8* buffer);
		u32		remove();
		void	scan();
		
		
		void	setPassword(char *n);
		char*	getPassword();
		
		User*	getUNext();
		void	setUNext(User* us);
		
		void	setUType(u32 t);
		u32		getUType();
		
	protected:
		u32		utype;
	
		User*	unext;
		char	password[512];
		
};

#endif
