
#include <os.h>
#include <null.h>

#include <api/dev/ioctl.h>

File* null_mknod(char* name,u32 flag,File* dev){
	Null* cons=new Null(name);
	return cons;
}

module("module.null",MODULE_DEVICE,Null,null_mknod)

Null::~Null(){
	
}

Null::Null(char* n) : Device(n)
{

}

void Null::scan(){

}

u32	Null::close(){
	return RETURN_OK;
}

u32	Null::open(u32 flag){
	return RETURN_OK;
}

u32	Null::read(u32 pos,u8* buffer,u32 size){
	memset((char*)buffer,0,size);
	return size;
}

u32	Null::write(u32 pos,u8* buffer,u32 size){
	return size;
}

u32	Null::ioctl(u32 id,u8* buffer){
	u32 ret=0;
	switch (id){
		case DEV_GET_TYPE:
			ret=DEV_TYPE_TTY;
			break;
			
		case DEV_GET_STATE:
			ret=DEV_STATE_OK;
			break;
			
		case DEV_GET_FORMAT:
			ret=DEV_FORMAT_CHAR;
			break;
	
		default:
			ret=NOT_DEFINED;
	}
	return ret;
}

u32	Null::remove(){
	delete this;
	return RETURN_OK;
}
