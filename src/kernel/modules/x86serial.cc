
#include <os.h>
#include <x86serial.h>

#include <api/dev/ioctl.h>
#include <api/dev/tty.h>


u8 X86Serial::init_serial=0;

File* x86serial_mknod(char* name,u32 flag,File* dev){
	X86Serial* cons=new X86Serial(name);
	return cons;
}

module("module.x86serial",MODULE_DEVICE,X86Serial,x86serial_mknod)

X86Serial::~X86Serial(){
	
}

X86Serial::X86Serial(char* n) : Device(n)
{

}


void X86Serial::putc(char c){
	while(io.inb(COM1 + 5) & 0x20 == 0 );
		io.outb(COM1,c);
}

char X86Serial::getc(){
	while(io.inb(COM1 + 5) & 0x1 == 0 );
	return (char)io.inb(COM1);
}

u32	X86Serial::open(u32 flag){
	if (init_serial==0){
		io.outb( COM1 + 1,	0x00 );	
		io.outb( COM1 + 3,	0x80 );	
		io.outb( COM1,		0x03 );	
		io.outb( COM1 + 1,	0x00 ); 
		io.outb( COM1 + 3, 0x03 );	
		io.outb( COM1 + 2, 0xC7 );	
		io.outb( COM1 + 4, 0x0B );	
		init_serial=1;
	}
	return RETURN_OK;
}

u32	X86Serial::close(){
	return RETURN_OK;
}

void X86Serial::scan(){

}

u32	X86Serial::read(u32 pos,u8* buffer,u32 sizee){
	int i;
	for (i=0;i<sizee;i++){
		*buffer=getc();
		buffer++;
	}
	return sizee;
}

u32	X86Serial::write(u32 pos,u8* buffer,u32 sizee){	
	int i;
	for (i=0;i<sizee;i++){
		putc(*buffer);
		buffer++;
	}
	return sizee;
}

u32	X86Serial::ioctl(u32 id,u8* buffer){
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
			break;
	}
	return ret;
}

u32	X86Serial::remove(){
	delete this;
	return RETURN_OK;
}
