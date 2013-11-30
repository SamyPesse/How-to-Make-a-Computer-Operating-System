
#ifndef __BOCHS_VBE__
#define __BOCHS_VBE__

#include <runtime/types.h>
#include <core/device.h>
#include <io.h>

#include <api/dev/ioctl.h>
#include <api/dev/fb.h>


#define VBE_DISPI_ENABLED (0x01)
#define VBE_DISPI_DISABLED (0x00)
#define VBE_DISPI_INDEX_ENABLE (4)
#define VBE_DISPI_ID4 (0xB0C4)
#define VBE_DISPI_LFB_ENABLED (0x40)
#define VBE_DISPI_NOCLEARMEM (0x80)
#define VBE_DISPI_IOPORT_INDEX (0x01CE)
#define VBE_DISPI_INDEX_ID (0)
#define VBE_DISPI_INDEX_XRES (1)
#define VBE_DISPI_INDEX_YRES (2)
#define VBE_DISPI_INDEX_BPP (3)
#define VBE_DISPI_INDEX_ENABLE (4)
#define VBE_DISPI_INDEX_BANK (5)
#define VBE_DISPI_INDEX_VIRT_WIDTH (6)
#define VBE_DISPI_INDEX_VIRT_HEIGHT (7)
#define VBE_DISPI_INDEX_X_OFFSET (8)
#define VBE_DISPI_INDEX_Y_OFFSET (9) 
#define VBE_DISPI_IOPORT_DATA (0x01CF)
 
#define VBE_DISPI_LFB_PHYSICAL_ADDRESS  0xE0000000


class Bochs : public Device
{
	public:
		Bochs(char* n);
		~Bochs();
		
		
		u32		open(u32 flag);
		u32		close();
		u32		read(u32 pos,u8* buffer,u32 size);
		u32		write(u32 pos,u8* buffer,u32 size);
		u32		ioctl(u32 id,u8* buffer);
		u32		remove();
		void	scan();
		
		
	private:
		fb_info	fbinfo_best;
		fb_info	fbinfo;
};

#endif
