
#ifndef _OS_SYSCALL_TABLE_H_
#define _OS_SYSCALL_TABLE_H_


#define NOT_DEFINED 0

enum {
	SYS_rewinddir			=NOT_DEFINED,
	SYS_sbrk				=45,	//	(count)
	SYS_fork				=NOT_DEFINED,
	SYS_write				=4,		//	(fd,buffer,count)
	SYS_read				=3,		//	(fd,buffer,count)
	SYS_open				=5,		//	(filename,flag)
	SYS_close				=6,		//	(fd)
	SYS_execve				=11,		//	(filename,argv,envp )
	SYS_dup					=NOT_DEFINED,
	SYS_dup2				=38,
	SYS_pwrite				=NOT_DEFINED,
	SYS_pread				=NOT_DEFINED,
	SYS_exit				=1,	//	(status)
	SYS_getdents			=89,
	SYS_fchdir				=NOT_DEFINED,
	SYS_isatty				=NOT_DEFINED,
	SYS_lseek				=19,
	SYS_unlink				=17,
	SYS_link				=18,
	SYS_readlink			=19,
	SYS_sleep_thread		=NOT_DEFINED,
	SYS_access				=NOT_DEFINED,
	SYS_chdir				=12,
	SYS_getpid				=20,
	SYS_getuid				=70,
	SYS_gettid				=NOT_DEFINED,
	SYS_rmdir				=NOT_DEFINED,
	SYS_symlink				=9,		//	(oldname,newname)
	SYS_fcntl				=NOT_DEFINED,
	SYS_get_system_time		=NOT_DEFINED,
	SYS_stat				=106,
	SYS_fstat				=NOT_DEFINED,
	SYS_stime				=NOT_DEFINED,
	SYS_mkdir				=15,
	SYS_ioctl				=54,	//	(fd,adress,buffer)
	SYS_select				=NOT_DEFINED,
	SYS_mount				=13,
	SYS_unmount				=14,
	SYS_lstat				=NOT_DEFINED,
	SYS_utime				=NOT_DEFINED,
	SYS_wait4				=7,
	SYS_socket				=NOT_DEFINED,
	SYS_connect				=NOT_DEFINED,
	SYS_sigaction			=67,
	SYS_kill				=37,
	SYS_sigprocmask			=NOT_DEFINED,
	SYS_dbprintf			=NOT_DEFINED,
	SYS_create_semaphore	=NOT_DEFINED,
	SYS_delete_semaphore	=NOT_DEFINED,
	SYS_lock_semaphore		=NOT_DEFINED,
	SYS_unlock_semaphore	=NOT_DEFINED,
	SYS_create_thread		=101,
	SYS_wake_up_thread		=NOT_DEFINED,
	SYS_kill_thread			=NOT_DEFINED,
	SYS_mmap				=55,
	
	SYS_loadmod				=71,
	SYS_login				=72,
	SYS_newuser				=73,
};




#endif 
