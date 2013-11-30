
#ifndef FILESYSTEM_H
#define FILESYSTEM_H

#include <runtime/types.h>
#include <core/file.h>


class Filesystem
{
	public:
		Filesystem();
		~Filesystem();
		
		void 	init();
		void	mknod(char* module,char* name,u32 flag);
		
		File* 	path(char* p);
		File* 	path_parent(char* p,char *fname);
		
		u32		link(char* fname,char *newf);
		
		
		u32 	addFile(char* dir,File* fp);
		
		File* 	pivot_root(File* targetdir);
		
		File*	getRoot();
		
	private:
		File*	root;
		File*	dev;
		File*	var;
};

extern Filesystem		fsm;
#endif
