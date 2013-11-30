
#include <os.h>
#include <clock_x86.h>

#include <api/dev/ioctl.h>


static void GetWeekday(unsigned int *Weekday)
{
	unsigned int DataWeekday;

	io.outb(0x70, 0x95);

	io.outb(0x70, 6);
	DataWeekday = io.inb(0x71);
	if(DataWeekday<6) *Weekday = DataWeekday + 2;
	else *Weekday = DataWeekday - 5;
}

static void GetDate(unsigned int *Year, unsigned int *Month, unsigned int *Day)
{
	unsigned int DataYear, DataMonth, DataDay;

	io.outb(0x70, 0x95);

	io.outb(0x70, 9);
	DataYear = io.inb(0x71);
	*Year = DataYear - ((unsigned int) DataYear/16) * 6;

	io.outb(0x70, 8);
	DataMonth = io.inb(0x71);
	*Month = DataMonth - ((unsigned int) DataMonth/16) * 6;

	io.outb(0x70, 7);
	DataDay = io.inb(0x71);
	*Day = DataDay - ((unsigned int) DataDay/16) * 6;
}

static void GetTime(unsigned int *Hour, unsigned int *Minute, unsigned int *Second)
{
	unsigned int DataHour, DataMinute, DataSecond;

	io.outb(0x70, 0x95);

	io.outb(0x70, 4);
	DataHour = io.inb(0x71);
	*Hour = DataHour - ((unsigned int) DataHour/16) * 6;

	io.outb(0x70, 2);
	DataMinute = io.inb(0x71);
	*Minute = DataMinute - ((unsigned int) DataMinute/16) * 6;	
	
	io.outb(0x70, 0);
	DataSecond = io.inb(0x71);
	*Second = DataSecond - ((unsigned int) DataSecond/16) * 6;
}




File* clockx86_mknod(char* name,u32 flag,File* dev){
	Clock_x86* cons=new Clock_x86(name);
	return cons;
}

module("module.clock_x86",MODULE_DEVICE,Clock_x86,clockx86_mknod)

Clock_x86::~Clock_x86(){
	
}

Clock_x86::Clock_x86(char* n) : Device(n)
{

}

void Clock_x86::scan(){

}

u32	Clock_x86::close(){
	return RETURN_OK;
}

u32	Clock_x86::open(u32 flag){
	return RETURN_OK;
}

u32	Clock_x86::read(u32 pos,u8* buffer,u32 size){
	return NOT_DEFINED;
}

u32	Clock_x86::write(u32 pos,u8* buffer,u32 size){
	return NOT_DEFINED;
}

void Clock_x86::reset_info(){
	GetDate(&(cinfo.year),&(cinfo.month), &(cinfo.day));
	GetTime(&(cinfo.h),&(cinfo.m), &(cinfo.s));
}

u32	Clock_x86::ioctl(u32 id,u8* buffer){
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
			
		case API_CLOCK_GET_INFO:
			reset_info();
			memcpy((char*)buffer,(char*)&cinfo,sizeof(clock_info));
			break;
	
		default:
			ret=NOT_DEFINED;
	}
	return ret;
}

u32	Clock_x86::remove(){
	delete this;
	return RETURN_OK;
}
