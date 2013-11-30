
#include <os.h>
#include <api/dev/proc.h>

/* Definis un process (/dev/proc) */

char* Process::default_tty="/dev/tty";

u32 Process::proc_pid=0;

Process::~Process(){
	delete ipc;
	arch.change_process_father(this,pparent);	//on change le pere des enfants	
}

Process::Process(char* n) : File(n,TYPE_PROCESS)
{
	fsm.addFile("/proc/",this);
	pparent=arch.pcurrent;
	pid=proc_pid;
	proc_pid++;
	if (pparent!=NULL)
		cdir=pparent->getCurrentDir();
	else
		cdir=fsm.getRoot();
		
	arch.addProcess(this);
	info.vinfo=(void*)this;
	int i;
	for (i=0;i<CONFIG_MAX_FILE;i++){	//open files
		openfp[i].fp=NULL;
	}
	ipc= new Buffer();	//ipc buffer
}

u32	Process::open(u32 flag){
	return RETURN_OK;
}

u32	Process::close(){
	return RETURN_OK;
}

Process* Process::getPParent(){
	return pparent;
}

void Process::setPParent(Process*p){
	pparent=p;
}

u32	Process::read(u32 pos,u8* buffer,u32 sizee){
	u32 ret=RETURN_OK;
	arch.enable_interrupt();
	while (ipc->isEmpty());
	ret=ipc->get(buffer,sizee);
	
	arch.disable_interrupt();
	return ret;
}

u32	Process::write(u32 pos,u8* buffer,u32 sizee){
	ipc->add(buffer,sizee);
	return size;
}

u32	Process::ioctl(u32 id,u8* buffer){
	u32 ret;
	switch (id){
		case API_PROC_GET_PID:
			ret= pid;
			break;
			
		case API_PROC_GET_INFO:
			reset_pinfo();
			memcpy((char*)buffer,(char*)&ppinfo,sizeof(proc_info));
			break;
			
			
		default:
			ret=NOT_DEFINED;
			break;
	}
	
	return ret;
}

int	Process::fork(){
	/*Process* p=new Process("fork_child");
	return arch.fork(p->getPInfo(),&info);*/
	if (pparent!=NULL)
		pparent->sendSignal(SIGCHLD);	
	return 0;
}

u32	Process::wait(){
	arch.enable_interrupt();
	while (is_signal(info.signal, SIGCHLD)==0);
	clear_signal(&(info.signal), SIGCHLD);
	arch.destroy_all_zombie();
	arch.disable_interrupt();
	return 1;
}

u32	Process::remove(){
	delete this;
	return RETURN_OK;
}

void Process::scan(){

}

void Process::exit(){
	setState(ZOMBIE);
	if (pparent!=NULL)
		pparent->sendSignal(SIGCHLD);
}

void Process::setPNext(Process* p){
	pnext=p;
}

process_st* Process::getPInfo(){
	return &info;
}

Process* Process::getPNext(){
	return pnext;
}

u32 Process::create(char* file, int argc, char **argv){
	int ret=arch.createProc(&info,file,argc,argv);
	if (ret==1)
		setState(CHILD);
	else
		setState(ZOMBIE);
		
	//stdin stdout et stderr du parent
	if (pparent!=NULL){
		memcpy((char*)&openfp[0],(char*)pparent->getFileInfo(0),sizeof(openfile));
		memcpy((char*)&openfp[1],(char*)pparent->getFileInfo(1),sizeof(openfile));
		memcpy((char*)&openfp[2],(char*)pparent->getFileInfo(2),sizeof(openfile));
		addFile(this,0);
	}
	else{
		addFile(fsm.path(default_tty),0);
		addFile(fsm.path(default_tty),0);
		addFile(fsm.path(default_tty),0);
		
	}
	
	return RETURN_OK;
}

void Process::setFile(u32 fd,File* fp,u32 ptr, u32 mode){
	if (fd<0 || fd>CONFIG_MAX_FILE)
		return;
	openfp[fd].fp=fp;
	openfp[fd].ptr=ptr;
	openfp[fd].mode=mode;
}

u32 Process::addFile(File* f,u32 m){
	int i;
	for (i=0;i<CONFIG_MAX_FILE;i++){
		if (openfp[i].fp==NULL && f!=NULL){
			//io.print("%s:  add %s in %d\n",name,f->getName(),i);
			openfp[i].fp=f;
			openfp[i].mode=m;
			openfp[i].ptr=0;
			return i;
		}
	}
}

File* Process::getFile(u32 fd){
	if (fd<0 || fd>CONFIG_MAX_FILE)
		return NULL;
	return openfp[fd].fp;
}

openfile* Process::getFileInfo(u32 fd){
	if (fd<0 || fd>CONFIG_MAX_FILE)
		return NULL;
	return &openfp[fd];
}

void Process::deleteFile(u32 fd){
	if (fd<0 || fd>CONFIG_MAX_FILE)
		return;
	openfp[fd].fp=NULL;
	openfp[fd].mode=0;
	openfp[fd].ptr=0;
}

Process* Process::schedule(){
	Process* n=this;
	int out=1;
	n=n->getPNext();
	while (out){
		
		if (n==NULL){
			n=arch.plist;
		}
		//io.print("testing %s\n",n->getName());
		
		
		if (n->getState() !=ZOMBIE){
			out=0;
		}
		else{
			n=n->getPNext();
		}
		
	}
	
	arch.pcurrent=n;
	
	return n;
}


File* Process::getCurrentDir(){
	return cdir;
}

void Process::setCurrentDir(File* f){
	cdir=f;
}



void Process::setState(u8 st){
	state=st;
}

u8	Process::getState(){
	return state;
}


void Process::setPid(u32 st){
	pid=st;
}

u32	Process::getPid(){
	return pid;
}

void Process::sendSignal(int sig){
	set_signal(&(info.signal),sig);
}

void Process::reset_pinfo(){
	strncpy(ppinfo.name,name,32);
	ppinfo.pid=pid;
	ppinfo.tid=0;
	ppinfo.state=state;
	ppinfo.vmem=10*1024*1024;
	ppinfo.pmem=10*1024*1024;
}

