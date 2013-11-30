
#include <os.h>
#include <bochsvbe.h>

/* Driver video pour bios VBE/Bios */


static void BgaWriteRegister(unsigned short IndexValue, unsigned short DataValue)
{
    io.outw(VBE_DISPI_IOPORT_INDEX, IndexValue);
    io.outw(VBE_DISPI_IOPORT_DATA, DataValue);
}
 
static unsigned short BgaReadRegister(unsigned short IndexValue)
{
    io.outw(VBE_DISPI_IOPORT_INDEX, IndexValue);
    return io.inw(VBE_DISPI_IOPORT_DATA);
}
 
static int BgaIsAvailable(void)
{
    return (BgaReadRegister(VBE_DISPI_INDEX_ID) == VBE_DISPI_ID4);
}
 
static void BgaSetVideoMode(unsigned int Width, unsigned int Height, unsigned int BitDepth, int UseLinearFrameBuffer, int ClearVideoMemory)
{
    BgaWriteRegister(VBE_DISPI_INDEX_ENABLE, VBE_DISPI_DISABLED);
    BgaWriteRegister(VBE_DISPI_INDEX_XRES, Width);
    BgaWriteRegister(VBE_DISPI_INDEX_YRES, Height);
    BgaWriteRegister(VBE_DISPI_INDEX_BPP, BitDepth);
    BgaWriteRegister(VBE_DISPI_INDEX_ENABLE, VBE_DISPI_ENABLED |
        (UseLinearFrameBuffer ? VBE_DISPI_LFB_ENABLED : 0) |
        (ClearVideoMemory ? 0 : VBE_DISPI_NOCLEARMEM));
}
 
static void BgaSetBank(unsigned short BankNumber)
{
    BgaWriteRegister(VBE_DISPI_INDEX_BANK, BankNumber);
}

File* bochs_mknod(char* name,u32 flag,File* dev){
	Bochs* cons=new Bochs(name);
	return cons;
}

module("module.bvbe",MODULE_DEVICE,Bochs,bochs_mknod)

Bochs::~Bochs(){
	
}

Bochs::Bochs(char* n) : Device(n)
{
	fbinfo_best.w=1024;
	fbinfo_best.h=768;
	fbinfo_best.bpp=32;
	fbinfo_best.state=FB_ACTIVE;
	fbinfo_best.vmem=(unsigned int*)VBE_DISPI_LFB_PHYSICAL_ADDRESS;
	
	fbinfo.w=0;
	fbinfo.h=0;
	fbinfo.bpp=0;
	fbinfo.state=FB_NOT_ACTIVE;
	fbinfo.vmem=(unsigned int*)VBE_DISPI_LFB_PHYSICAL_ADDRESS;
	map_memory=(char*)VBE_DISPI_LFB_PHYSICAL_ADDRESS;
}

u32	Bochs::open(u32 flag){
	return RETURN_OK;
}

u32	Bochs::read(u32 pos,u8* buffer,u32 size){
	return NOT_DEFINED;
}

u32	Bochs::write(u32 pos,u8* buffer,u32 size){
	return NOT_DEFINED;
}

u32	Bochs::close(){
	return RETURN_OK;
}

void Bochs::scan(){

}


u32	Bochs::ioctl(u32 id,u8* buffer){
	u32 ret=0;
	switch (id){
		case DEV_GET_TYPE:
			ret=DEV_TYPE_FB;
			break;
			
		case DEV_GET_STATE:
			ret=DEV_STATE_OK;
			break;
			
		case DEV_GET_FORMAT:
			ret=DEV_FORMAT_FB;
			break;
			
			
		case API_FB_IS_AVAILABLE:
			ret=(u32)BgaIsAvailable();
			break;
			
		case API_FB_GET_INFO:
			memcpy((char*)buffer,(char*)&fbinfo,sizeof(fb_info));
			break;
			
		case API_FB_SET_INFO:
			memcpy((char*)&fbinfo,(char*)buffer,sizeof(fb_info));
			BgaSetVideoMode(fbinfo.w, fbinfo.h, (unsigned int)fbinfo.bpp/8, 1, 1);
			break;
			
		case API_FB_GET_BINFO:
			memcpy((char*)buffer,(char*)&fbinfo_best,sizeof(fb_info));
			break;
			
		default:
			ret=NOT_DEFINED;
			break;
	}
	return ret;
}

u32	Bochs::remove(){
	delete this;
	return RETURN_OK;
}
