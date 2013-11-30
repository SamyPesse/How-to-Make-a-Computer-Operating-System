
#include <os.h>

/* dans myos quasiment tous herite de cette classe */


/*
 *	Remplace dans s tous les a par to
 */
static void strreplace(char* s,char a,char to){
	if (s==NULL)
		return;
	while (*s){
		if (*s==a)
			*s=to;
		s++;
	}
}


u32	File::inode_system=0;	/* numero d'inode de depart */

/* constructeur */
File::File(char* n,u8 t){
	name=(char*)kmalloc(strlen(n)+1);
	memset(name,0,strlen(n));
	memcpy(name,n,strlen(n));
	name[strlen(n)]=0;
	
	checkName();
	master=arch.pcurrent;	//à la creation, le maitre est le processus courant
	inode=inode_system;
	inode_system++;
	size=0;
	type=t;
	parent=NULL;
	child=NULL;
	next=NULL;
	prec=NULL;
	link=NULL;
	map_memory=NULL;
}

/* destructeur */
File::~File(){
	kfree(name);
	
	//on modifie la liste des frere
	
	if (prec==NULL){
		parent->setChild(next);
		next->setPrec(NULL);
	}
	else if (next==NULL){
		prec->setNext(NULL);
	}
	else if (next==NULL && prec==NULL){
		parent->setChild(NULL);
	}
	else{
		io.print("prec (%s) next is now %s\n",prec->getName(),next->getName());
		io.print("next (%s) prec is now %s\n",next->getName(),prec->getName());
		prec->setNext(next);
		next->setPrec(prec);
	}
	
	//on supprime les enfant (dossier)
	File* n=child;
	File* nn=NULL;
	while (n!=NULL){
		//io.print("delete %s \n",n->getName());
		nn=n->getNext();
		delete n;
		n=nn;
	}
	
}

#define CAR_REPLACE '_'


void File::checkName(){
	//Adapte le nom
	strreplace(name,'/',CAR_REPLACE);
	strreplace(name,'\ ',CAR_REPLACE);
	strreplace(name,'?',CAR_REPLACE);
	strreplace(name,':',CAR_REPLACE);
	strreplace(name,'>',CAR_REPLACE);
	strreplace(name,'<',CAR_REPLACE);
	strreplace(name,'*',CAR_REPLACE);
	strreplace(name,'"',CAR_REPLACE);
	strreplace(name,':',CAR_REPLACE);
}

u32 File::addChild(File* n){
	if (!n){
		return PARAM_NULL;
	}
	n->setParent(this);
	n->setPrec(NULL);
	n->setNext(child);
	if (child != NULL)
		child->setPrec(n);
	child=n;
	return RETURN_OK;
}

File*	File::createChild(char* n,u8 t){
	File* fp=new File(n,t);
	addChild(fp);
	return fp;
}

File*	File::getParent(){
	return parent;
}

File*	File::getChild(){
	return child;
}

File*	File::getNext(){
	return next;
}

File*	File::getPrec(){
	return prec;
}

File*	File::getLink(){
	return link;
}

u32	File::getSize(){
	return size;
}

u32	File::getInode(){
	return inode;
}

void File::scan(){

}

void	File::setType(u8 t){
	type=t;
}

void	File::setSize(u32 t){
	size=t;
}

void	File::setParent(File* n){
	parent=n;
}

void	File::setLink(File* n){
	link=n;
}

void	File::setChild(File* n){
	child=n;
}

void	File::setNext(File* n){
	next=n;
}

void	File::setPrec(File* n){
	prec=n;
}

void	File::setName(char* n){
	kfree(name);
	name=(char*)kmalloc(strlen(n));
	memcpy(name,n,strlen(n));
	checkName();
}

u8	File::getType(){
	return type;
}

char* File::getName(){
	return name;
}

File* File::find(char* n){
	File* fp=child;
	while (fp!=0){
		if (!strcmp(fp->getName(),n))
			return fp;
		
		fp=fp->next;
	}
	return NULL;
}



u32	File::open(u32 flag){
	return NOT_DEFINED;
}

u32	File::close(){
	return NOT_DEFINED;
}

u32	File::read(u32 pos,u8* buffer,u32 size){
	return NOT_DEFINED;
}

u32	File::write(u32 pos,u8* buffer,u32 size){
	return NOT_DEFINED;
}

u32	File::ioctl(u32 id,u8* buffer){
	return NOT_DEFINED;
}

u32	File::remove(){
	delete this;
	return NOT_DEFINED;
}

stat_fs File::stat(){
	stat_fs st;
	
	return st;
}

u32 File::mmap(u32 sizee,u32 flags,u32 offset,u32 prot){
	if (map_memory!=NULL){
		int i=0;
		unsigned int adress;
		struct page *pg;
		process_st* current=(arch.pcurrent)->getPInfo();
		for (i=0;i<sizee;i++){
				adress=(unsigned int)(map_memory+i*PAGESIZE);
				//io.print("mmap : %x %d\n",adress,sizee);
				pg = (struct page *) kmalloc(sizeof(struct page));
				pg->p_addr = (char*) (adress);
				pg->v_addr = (char *) (adress & 0xFFFFF000);
				list_add(&pg->list, &current->pglist);
				pd_add_page(pg->v_addr, pg->p_addr, PG_USER, current->pd);
		}
		return (u32)map_memory;
	}
	else{
		return -1;
	}
}

