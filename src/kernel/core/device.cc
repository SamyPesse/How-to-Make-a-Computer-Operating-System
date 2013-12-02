#include <os.h>



Device::~Device(){
	
}

Device::Device(char* n) : File(n,TYPE_DEVICE)
{
	fsm.addFile("/dev",this);
}

u32	Device::open(u32 flag){
	return NOT_DEFINED;
}

u32	Device::close(){
	return NOT_DEFINED;
}

u32	Device::read(u8* buffer,u32 size){
	return NOT_DEFINED;
}

u32	Device::write(u8* buffer,u32 size){
	return NOT_DEFINED;
}

u32	Device::ioctl(u32 id,u8* buffer){
	return NOT_DEFINED;
}

u32	Device::remove(){
	delete this;
}

void Device::scan(){

}

