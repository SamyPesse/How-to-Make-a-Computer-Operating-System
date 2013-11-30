
#include <os.h>
#include <stdtty.h>




File* console_mknod(char* name,u32 flag,File* dev){
	Console* cons=new Console(name,flag);
	return cons;
}

module("module.stdio",MODULE_DEVICE,Console,console_mknod)

Console::~Console(){
	if (iotty!=&io)
		delete iotty;
}

Console::Console(char* n,u32 flag) : Device(n)
{
	if (flag==0)
		iotty=new Io(flag);
	else
		iotty=&io;
}

void Console::reset_info(){
	//static info
	strncpy(sinfo.name,name,TTY_NAME_LEN);
	sinfo.state=TTY_STATE_RUN;
	sinfo.type=TTY_TYPE_IOSTD;
	sinfo.flags=0;
	
	//moving info
	minfo.x=iotty->getX();
	minfo.y=iotty->getY();
	minfo.attrf=White;
	minfo.attrb=Black;
}

void Console::scan(){

}

u32	Console::open(u32 flag){
	return RETURN_OK;
}

u32	Console::close(){
	return RETURN_OK;
}

u32	Console::read(u32 pos,u8* buffer,u32 sizee){
	return iotty->read((char*)buffer,sizee);
}

u32	Console::write(u32 pos,u8* buffer,u32 size){	
	int i;
	for (i=0;i<size;i++){
		iotty->putc(*buffer);
		buffer++;
	}
	return size;
}

u32	Console::ioctl(u32 id,u8* buffer){
	u32 ret=0;
	reset_info();
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
			
		case API_TTY_SWITCH_SCREEN:
			iotty->switchtty();
			break;
			
		case API_TTY_CLEAR_SCREEN:
			iotty->clear();
			break;
			
		case API_TTY_GET_SINFO:
			memcpy((char*)buffer,(char*)&sinfo,sizeof(tty_info_static));
			break;
			
		case API_TTY_GET_MINFO:
			memcpy((char*)buffer,(char*)&minfo,sizeof(tty_info_moving));
			break;
			
		case API_TTY_SET_MINFO:
			break;
			
		default:
			ret=NOT_DEFINED;
			break;
	}
	return ret;
}

u32	Console::remove(){
	delete this;
	return RETURN_OK;
}
