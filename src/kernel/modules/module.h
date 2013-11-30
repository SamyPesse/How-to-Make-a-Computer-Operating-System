
#ifndef __MODULE__
#define __MODULE__

#include <runtime/types.h>
#include <core/file.h>
#include <io.h>


#define NO_FLAG	0

class Module
{
	public:
		Module();
		~Module();
		
		void 	initLink();
		void 	init();
		
		File*	createDevice(char* name,char* module,u32 flag);
		File*	mount(char* dev,char* dir,char* module,u32 flag);
		File*	install(char* dir,char* module,u32 flag,char* dev);
};

extern Module	modm;

#endif
