
#include <os.h>
#include <ide.h>

#include <api/dev/ioctl.h>


/*
 *	Cette fonction attend que le disque soit pret avant une operation
 */
int bl_wait(unsigned short base)
{
	while(io.inb(base+0x206) & 0x80);
	return 0;	
}

/*
 *	Cette fonction permet de ce deplacer sur le disque
 */
int bl_common(int drive, int numblock, int count)
{
	bl_wait(0x1F0);
	
	io.outb(0x1F1, 0x00);	/* NULL byte to port 0x1F1 */
	io.outb(0x1F2, count);	/* Sector count */
	io.outb(0x1F3, (unsigned char) numblock);	/* Low 8 bits of the block address */
	io.outb(0x1F4, (unsigned char) (numblock >> 8));	/* Next 8 bits of the block address */
	io.outb(0x1F5, (unsigned char) (numblock >> 16));	/* Next 8 bits of the block address */

	/* Drive indicator, magic bits, and highest 4 bits of the block address */
	io.outb(0x1F6, 0xE0 | (drive << 4) | ((numblock >> 24) & 0x0F));

	return 0;
}

/*
 *	Cette fonction permet de lire un buffer sur le disque
 */
int bl_read(int drive, int numblock, int count, char *buf)
{
	u16 tmpword;
	int idx;

	bl_common(drive, numblock, count);
	io.outb(0x1F7, 0x20);

	bl_wait(0x1F0);
	while (!(io.inb(0x1F7) & 0x08));

	for (idx = 0; idx < 256 * count; idx++) {
		tmpword = io.inw(0x1F0);
		buf[idx * 2] = (unsigned char) tmpword;
		buf[idx * 2 + 1] = (unsigned char) (tmpword >> 8);
	}
	return count;
}

/*
 *	Cette fonction permet d'ecrire un buffer sur le disque
 */
int bl_write(int drive, int numblock, int count, char *buf)
{
	u16 tmpword;
	int idx;

	bl_common(drive, numblock, count);
	io.outb(0x1F7, 0x30);
	bl_wait(0x1F0);
	/* Wait for the drive to signal that it's ready: */
	while (!(io.inb(0x1F7) & 0x08));

	for (idx = 0; idx < 256 * count; idx++) {
		tmpword = (buf[idx * 2 + 1] << 8) | buf[idx * 2];
		io.outw(0x1F0, tmpword);
	}

	return count;
}




File* ide_mknod(char* name,u32 flag,File* dev){
	Ide* disk=new Ide(name);
	disk->setId(flag);
	return disk;
}

module("module.ide",MODULE_DEVICE,Ide,ide_mknod)

Ide::~Ide(){
	
}

Ide::Ide(char* n) : Device(n)
{
	
}

u32	Ide::close(){
	return RETURN_OK;
}

void Ide::scan(){
	
}

u32	Ide::open(u32 flag){
	return RETURN_OK;
}

u32	Ide::read(u32 pos,u8* buffer,u32 sizee){
	int count=(int)sizee;
	
	if (buffer==NULL)
		return -1;
	
	int offset=(int)pos;
	int bl_begin, bl_end, blocks;

	bl_begin = (offset/512);
	bl_end = ((offset + count)/512);
	blocks = bl_end - bl_begin + 1;
	//io.print("%s> read at %d - %d  size=%d begin=%d blocks=%d\n",getName(),offset,offset/512,count,bl_begin,blocks);
	char*bl_buffer = (char *) kmalloc(blocks * 512);
	bl_read(id, bl_begin, blocks,bl_buffer);
	memcpy((char*)buffer, (char *) ((int)bl_buffer + ((int)offset % (int)(512))), count);
	kfree(bl_buffer);
	return count;
}

u32	Ide::write(u32 pos,u8* buffer,u32 sizee){
	return NOT_DEFINED;
}

u32	Ide::ioctl(u32 idd,u8* buffer){
	u32 ret=0;
	switch (idd){
		case DEV_GET_TYPE:
			ret=DEV_TYPE_DISK;
			break;
			
		case DEV_GET_STATE:
			ret=DEV_STATE_OK;
			break;
			
		case DEV_GET_FORMAT:
			ret=DEV_FORMAT_BLOCK;
			break;
			
		default:
			ret=NOT_DEFINED;
			break;
	}	
	return ret;
}



u32	Ide::remove(){
	delete this;
	return RETURN_OK;
}

void Ide::setId(u32 flag){
	id=flag;
}
