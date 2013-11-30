
#include <os.h>



ModLink::~ModLink(){
	
}

ModLink::ModLink(char* n) : File(n,TYPE_FILE)
{
	fsm.addFile("/sys/mods/",this);
}

u32	ModLink::open(u32 flag){
	return RETURN_OK;
}

u32	ModLink::close(){
	return RETURN_OK;
}

u32	ModLink::read(u8* buffer,u32 size){
	return NOT_DEFINED;
}

u32	ModLink::write(u8* buffer,u32 size){
	return NOT_DEFINED;
}

u32	ModLink::ioctl(u32 id,u8* buffer){
	return NOT_DEFINED;
}

u32	ModLink::remove(){
	delete this;
}

void ModLink::scan(){

}

