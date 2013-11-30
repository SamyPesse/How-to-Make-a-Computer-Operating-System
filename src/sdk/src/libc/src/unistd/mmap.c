
 

#include <errno.h>
#include <unistd.h>

#include <os.h>

void * mmap (void *addr,size_t len,int prot,int flags,int fd,off_t offset){
	return (void*)syscall5(SYS_mmap,(uint32_t) len, (uint32_t) prot, (uint32_t) flags,(uint32_t) fd,(uint32_t) offset);
}

