#ifndef __API_PROC__
#define __API_PROC__

struct proc_info{
	char				name[32];
	unsigned int		pid;
	unsigned int		tid;
	unsigned char		state;
	unsigned int		vmem;
	unsigned int		pmem;
};

enum{
	PROC_STATE_RUN=0,
	PROC_STATE_ZOMBIE=1,
	PROC_STATE_THREAD=2,
};

#define API_PROC_GET_PID		0x5200
#define API_PROC_GET_INFO		0x5201

#endif
