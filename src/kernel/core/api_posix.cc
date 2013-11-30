#include <os.h>


/*
 *	u32 open(char* name,u32 flag);
 */
void call_open(){
	char*name=(char*)arch.getArg(0);
	u32 flag=arch.getArg(1);
	
	Process* p=arch.pcurrent;
	if (p==NULL){
		arch.setRet((u32)-1);
		return;
	}
	
	File* fp=fsm.path(name);
	fp->open(flag);
	u32 fd=p->addFile(fp,flag);
	
	arch.setRet(fd);
}

/*
 *	void close(u32 fd);
 */
void call_close(){
	u32 fd=arch.getArg(0);
	Process* p=arch.pcurrent;
	if (p==NULL){
		arch.setRet((u32)-1);
		return;
	}
		
	File* fp=p->getFile(fd);
	if (fp==NULL){
		return;
	}
	
	fp->close();
	p->deleteFile(fd);
}

/*
 *	u32 read(u32 fd,char* buf,u32 size);
 */
void call_read(){
	u32 fd=arch.getArg(0);
	u8*buf=(u8*)arch.getArg(1);
	u32 size=arch.getArg(2);
	
	Process* p=arch.pcurrent;
	if (p==NULL){
		arch.setRet((u32)-1);
		return;
	}
		
	File* fp=p->getFile(fd);
	if (fp==NULL){
		arch.setRet((u32)-1);
		return;
	}
	openfile* info = p->getFileInfo(fd);
	u32 ret=fp->read(info->ptr,buf,size);
	info->ptr=info->ptr + ret;
	arch.setRet(ret);
}

/*
 *	u32 write(u32 fd,char* buf,u32 size);
 */
void call_write(){
	u32 fd=arch.getArg(0);
	u8*buf=(u8*)arch.getArg(1);
	u32 size=arch.getArg(2);
	
	Process* p=arch.pcurrent;
	if (p==NULL){
		arch.setRet((u32)-1);
		return;
	}
		
	File* fp=p->getFile(fd);
	if (fp==NULL){
		arch.setRet(-1);
		return;
	}
	openfile* info = p->getFileInfo(fd);
	u32 ret=fp->write(info->ptr,buf,size);
	info->ptr=info->ptr + ret;
	arch.setRet(ret);
}

/*
 *	u32 ioctl(u32 fd,u32 pos,char* buf);
 */
void call_ioctl(){
	u32 fd=arch.getArg(0);
	u8*buf=(u8*)arch.getArg(2);
	u32 pos=arch.getArg(1);
	
	Process* p=arch.pcurrent;
	if (p==NULL){
		arch.setRet((u32)-1);
		return;
	}
		
	File* fp=p->getFile(fd);
	if (fp==NULL){
		arch.setRet(-1);
		return;
	}
	
	u32 ret=fp->ioctl(pos,buf);
	arch.setRet(ret);
}

/*
 *	char* sbrk(int size);
 */
void call_sbrk(){
	int size;
	size=arch.getArg(0);
	char *ret;
	Process* p=arch.pcurrent;
	process_st* current=p->getPInfo();
	ret = current->e_heap;

	current->e_heap += size;
	
	arch.setRet((u32)ret);
	return;
}


/*
 *	void exit(int code);
 */
void call_exit(){
	int code;
	code=arch.getArg(0);
	
	Process* p=arch.pcurrent;
	p->exit();
	return;
}

/*
 *	int execv(const char* filename, char* const argv[], char* const envp[] );
 */
void call_execv(){
	char* filename,**argv,**envp;
	filename=(char*)arch.getArg(0);
	argv=(char**)arch.getArg(1);
	envp=(char**)arch.getArg(2);
	int argc;
	char **ap;
	
	ap = argv;
	argc = 0;
	while (*ap++) 
		argc++;
		
	int ret=execv(filename,argc,argv);
	arch.setRet((u32)ret);
	return;
}


/*
 *	int symlink(const char* oldpath, const char* newpath);
 */
void call_symlink(){
	char* oldpath,*path;
	oldpath=(char*)arch.getArg(0);
	path=(char*)arch.getArg(1);

	int ret=fsm.link(oldpath,path);
	arch.setRet((u32)ret);
	return;
}

struct dirent {
    u64	 d_ino;
    char d_name[256];
};

/*
 *	int getdents(int fd,dirrent* entry,int size);
 */
void call_getdents(){
	dirent nentry;
	u32 fd=arch.getArg(0);
	dirent* entry=(dirent*)arch.getArg(1);
	int size=arch.getArg(2);
	
	Process* p=arch.pcurrent;
	if (p==NULL){
		arch.setRet((u32)0);
		return;
	}
	
	File* fp=p->getFile(fd);
	if (fp==NULL){
		arch.setRet(0);
		return;
	}
	openfile* info = p->getFileInfo(fd);
	int i=0;
	File* child=fp->getChild();
	while (child!=NULL){
		if (i==(info->ptr)){
			//io.print("readdir=%s  - size=%d  entry=%x\n",child->getName(),size,entry);
			nentry.d_ino=child->getInode();
			strncpy(nentry.d_name,child->getName(),256);
			memcpy((char*)entry,(char*)&nentry,size);
			info->ptr++;
			arch.setRet(1);
			return;
		}
		i++;
		child=child->getNext();
	}
	arch.setRet((u32)0);
	return;
}

/*
 *	int wait(int* status);
 */
void call_wait(){
	u32*status=(u32*)arch.getArg(1);
	*status=0;
	Process* p=arch.pcurrent;
	u32 ret=p->wait();
	//arch.setRet(ret);
}

/*
 *	int dup2( int old_fd, int new_fd );
 */
void call_dup2(){
	u32 oldfd=arch.getArg(0);
	u32 newfd=arch.getArg(1);
	//io.print("dup2 %d to %d\n",oldfd,newfd);
	u32 ret=newfd;
	Process* p=arch.pcurrent;
	p->setFile((u32)newfd,p->getFile(oldfd),0, 0);
	arch.setRet((u32)ret);
}

/*
 *	int fork();
 */
void call_fork(){
	Process* p=arch.pcurrent;
	int ret=p->fork();
	arch.setRet((u32)ret);
}
 
/*
 *	int chdir(char* n);
 */
void call_chdir(){
	char* n;
	n=(char*)arch.getArg(0);
	
	Process* p=arch.pcurrent;
	File*f=fsm.path(n);
	if (f==NULL){
		arch.setRet((u32)-1);
		return;
	}
	
	p->setCurrentDir(f);
	arch.setRet((u32)1);
	return;
}

/*
 *	void * mmap (void *addr,size_t len,int prot,int flags,int fd,off_t offset)
 */
void call_mmap(){
	u32 fd=arch.getArg(3);
	u32 size=arch.getArg(0);
	u32 prot=0;
	u32 flags=0;
	u32 offset=0;
	
	Process* p=arch.pcurrent;
	if (p==NULL){
		arch.setRet((u32)-1);
		return;
	}
		
	File* fp=p->getFile(fd);
	if (fp==NULL){
		arch.setRet((u32)-1);
		return;
	}
	openfile* info = p->getFileInfo(fd);
	u32 ret=fp->mmap(size,flags,offset,prot);
	arch.setRet(ret);
}
