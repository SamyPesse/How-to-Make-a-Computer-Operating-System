#include <os.h>
#include <x86.h>

/* Stack pointer */
extern u32 *		stack_ptr;

/* Current cpu name */
static char cpu_name[512] = "x86-noname";


/* Detect the type of processor */
char* Architecture::detect(){
	cpu_vendor_name(cpu_name);
	return cpu_name;
}

/* Start and initialize the architecture */
void Architecture::init(){
	 io.print("Architecture x86, cpu=%s \n", detect());
	
	 io.print("Loading GDT \n");
		 init_gdt();
		 asm("	movw $0x18, %%ax \n \
			movw %%ax, %%ss \n \
			movl %0, %%esp"::"i" (KERN_STACK));
		
	 io.print("Loading IDT \n");
		 init_idt();
		
		
	 io.print("Configure PIC \n");
		 init_pic();
	 
	 io.print("Loading Task Register \n");
		 asm("	movw $0x38, %ax; ltr %ax");	 
}

/* Initialise the list of processus */
void Architecture::initProc(){
	firstProc= new Process("kernel");
	firstProc->setState(ZOMBIE);
	firstProc->addFile(fsm.path("/dev/tty"),0);
	firstProc->addFile(fsm.path("/dev/tty"),0);
	firstProc->addFile(fsm.path("/dev/tty"),0);
	
	
	plist=firstProc;
	pcurrent=firstProc; 
	pcurrent->setPNext(NULL);
	process_st* current=pcurrent->getPInfo();
	current->regs.cr3 = (u32) pd0;
}

/* Reboot the computer */
void Architecture::reboot(){
    u8 good = 0x02;
    while ((good & 0x02) != 0)
        good = io.inb(0x64);
    io.outb(0x64, 0xFE);
}

/* Shutdown the computer */
void Architecture::shutdown(){
	// todo
}

/* Install a interruption handler */
void Architecture::install_irq(int_handler h){
	// todo
}

/* Add a process to the scheduler */
void Architecture::addProcess(Process* p){
	p->setPNext(plist);
	plist=p;
}

/* Fork a process */
int Architecture::fork(process_st* info,process_st* father){
	memcpy((char*)info,(char*)father,sizeof(process_st));
	info->pd = pd_copy(father->pd);
}

/* Initialise a new process */
int Architecture::createProc(process_st* info, char* file, int argc, char** argv){
	page *kstack;
	process_st *previous;
	process_st *current;

	char **param, **uparam;
	u32 stackp;
	u32 e_entry; 

	
	int pid;
	int i;

	pid = 1;

	info->pid = pid;
	
	if (argc) {
		param = (char**) kmalloc(sizeof(char*) * (argc+1));
		for (i=0 ; i<argc ; i++) {
			param[i] = (char*) kmalloc(strlen(argv[i]) + 1);
			strcpy(param[i], argv[i]);
		}
		param[i] = 0;
	}
	
	info->pd = pd_create();


	INIT_LIST_HEAD(&(info->pglist));


	previous = arch.pcurrent->getPInfo();
	current=info;
	
	asm("mov %0, %%eax; mov %%eax, %%cr3"::"m"((info->pd)->base->p_addr));
	
	e_entry = (u32) load_elf(file,info);

	if (e_entry == 0) {	
		for (i=0 ; i<argc ; i++) 
			kfree(param[i]);
		kfree(param);
		arch.pcurrent = (Process*) previous->vinfo;
		current=arch.pcurrent->getPInfo();
		asm("mov %0, %%eax ;mov %%eax, %%cr3"::"m" (current->regs.cr3));
		pd_destroy(info->pd);
		return -1;
	}


	stackp = USER_STACK - 16;


	if (argc) {
		uparam = (char**) kmalloc(sizeof(char*) * argc);

		for (i=0 ; i<argc ; i++) {
			stackp -= (strlen(param[i]) + 1);
			strcpy((char*) stackp, param[i]);
			uparam[i] = (char*) stackp;
		}

		stackp &= 0xFFFFFFF0;	

		// Creation des arguments de main() : argc, argv[]... 
		stackp -= sizeof(char*);
		*((char**) stackp) = 0;

		for (i=argc-1 ; i>=0 ; i--) {		
			stackp -= sizeof(char*);
			*((char**) stackp) = uparam[i]; 
		}

		stackp -= sizeof(char*);	
		*((char**) stackp) = (char*) (stackp + 4); 

		stackp -= sizeof(char*);	
		*((int*) stackp) = argc; 

		stackp -= sizeof(char*);

		for (i=0 ; i<argc ; i++) 
			kfree(param[i]);

		kfree(param);
		kfree(uparam);
	}

	
	kstack = get_page_from_heap();


	// Initialise le reste des registres et des attributs 
	info->regs.ss = 0x33;
	info->regs.esp = stackp;
	info->regs.eflags = 0x0;
	info->regs.cs = 0x23;
	info->regs.eip = e_entry;
	info->regs.ds = 0x2B;
	info->regs.es = 0x2B;
	info->regs.fs = 0x2B;
	info->regs.gs = 0x2B;
	info->regs.cr3 = (u32) info->pd->base->p_addr;

	info->kstack.ss0 = 0x18;
	info->kstack.esp0 = (u32) kstack->v_addr + PAGESIZE - 16;

	info->regs.eax = 0;
	info->regs.ecx = 0;
	info->regs.edx = 0;
	info->regs.ebx = 0;

	info->regs.ebp = 0;
	info->regs.esi = 0;
	info->regs.edi = 0;

	info->b_heap = (char*) ((u32) info->e_bss & 0xFFFFF000) + PAGESIZE;
	info->e_heap = info->b_heap;

	info->signal = 0;
	for(i=0 ; i<32 ; i++)
		info->sigfn[i] = (char*) SIG_DFL;

	arch.pcurrent = (Process*) previous->vinfo;
	current=arch.pcurrent->getPInfo();
	asm("mov %0, %%eax ;mov %%eax, %%cr3":: "m"(current->regs.cr3));
	
	return 1;
}


// Destroy a process
void Architecture::destroy_process(Process* pp){
	disable_interrupt();
	
	u16 kss;
	u32 kesp;
	u32 accr3;
	list_head *p, *n;
	page *pg;
	process_st *proccurrent=(arch.pcurrent)->getPInfo();
	process_st *pidproc=pp->getPInfo();
	
	
	// Switch page to the process to destroy
	asm("mov %0, %%eax ;mov %%eax, %%cr3"::"m" (pidproc->regs.cr3));

	
	// Free process memory:
	//  - pages used by the executable code
	//  - user stack
	//  - kernel stack
	//  - pages directory

	// Free process memory
	list_for_each_safe(p, n, &pidproc->pglist) {
		pg = list_entry(p, struct page, list);
		release_page_frame(pg->p_addr);
		list_del(p);
		kfree(pg);
	}
	
	release_page_from_heap((char *) ((u32)pidproc->kstack.esp0 & 0xFFFFF000));

	// Free pages directory
	asm("mov %0, %%eax; mov %%eax, %%cr3"::"m"(pd0));

	pd_destroy(pidproc->pd);

	asm("mov %0, %%eax ;mov %%eax, %%cr3"::"m" (proccurrent->regs.cr3));
	
	// Remove from the list
	if (plist==pp){
		plist=pp->getPNext();
	}
	else{
		Process* l=plist;
		Process*ol=plist;
		while (l!=NULL){
			
			if (l==pp){
				ol->setPNext(pp->getPNext());
			}
			
			ol=l;
			l=l->getPNext();
		}
	}
	
	enable_interrupt();
}


void Architecture::change_process_father(Process* pe, Process* pere){
	Process* p=plist;
	Process* pn=NULL;
	while (p!=NULL){
		pn=p->getPNext();
		if (p->getPParent()==pe){
			p->setPParent(pere);
		}
		
		p=pn;
	}
}


void Architecture::destroy_all_zombie(){
	Process* p=plist;
	Process* pn=NULL;
	while (p!=NULL){
		pn=p->getPNext();
		if (p->getState()==ZOMBIE && p->getPid()!=1){
			destroy_process(p);
			delete p;
		}
		
		p=pn;
	}
}

/* Set the syscall arguments */
void Architecture::setParam(u32 ret, u32 ret1, u32 ret2, u32 ret3,u32 ret4){
	ret_reg[0]=ret;
	ret_reg[1]=ret1;
	ret_reg[2]=ret2;
	ret_reg[3]=ret3;
	ret_reg[4]=ret4;
}

/* Enable the interruption */
void Architecture::enable_interrupt(){
	asm ("sti");
}

/* Disable the interruption */
void Architecture::disable_interrupt(){
	asm ("cli");
}

/* Get a syscall argument */
u32	Architecture::getArg(u32 n){
	if (n<5)
		return ret_reg[n];
	else
		return 0;
}

/* Set the return value of syscall */
void Architecture::setRet(u32 ret){
	stack_ptr[14] = ret;
}
