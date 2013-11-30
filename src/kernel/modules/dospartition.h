
#ifndef __DOS_PARTITION__
#define __DOS_PARTITION__

#include <runtime/types.h>
#include <core/file.h>
#include <io.h>

#define DOS_PART_1	0x01BE
#define DOS_PART_2	0x01CE
#define DOS_PART_3	0x01DE
#define DOS_PART_4	0x01EE

struct dos_partition {
	u8 bootable;			/* 0 = no, 0x80 = bootable */
	u8 s_head;				/* Starting head */
	u16 s_sector:6;			/* Starting sector */
	u16 s_cyl:10;			/* Starting cylinder */
	u8 id;					/* System ID */
	u8 e_head;				/* Ending Head */
	u16 e_sector:6;			/* Ending Sector */
	u16 e_cyl:10;			/* Ending Cylinder */
	u32 s_lba;				/* Starting LBA value */
	u32 size;				/* Total Sectors in partition */
} __attribute__ ((packed));
 
/*
 *	Driver class
 */
class DosPartition : public Device
{
	public:
		DosPartition(char* n,File* dev,u32 num);
		~DosPartition();
		
		
		u32		open(u32 flag);
		u32		close();
		u32		read(u32 pos,u8* buffer,u32 sizee);
		u32		write(u32 pos,u8* buffer,u32 sizee);
		u32		ioctl(u32 id,u8* buffer);
		u32		remove();
		void	scan();
		

	private:
		u32 			numpart;
		dos_partition*	partition_info;
};

#endif
