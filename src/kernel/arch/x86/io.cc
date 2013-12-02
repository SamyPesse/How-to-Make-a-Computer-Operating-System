#include <os.h>

Io* Io::last_io=&io;		/* definis la derniere io avant switch */
Io* Io::current_io=&io;		/* interface actuel (clavier redirigé vers celle ci) */

/* Video memory */
char* Io::vidmem = (char*)RAMSCREEN;

/* Constructor */
Io::Io(){
	real_screen = (char*)RAMSCREEN;
}

/* Destructor */
Io::Io(u32 flag){
	real_screen=(char*)screen;
}

/* output byte */
void Io::outb(u32 ad,u8 v){
	asmv("outb %%al, %%dx" :: "d" (ad), "a" (v));;
}
/* output word */
void Io::outw(u32 ad,u16 v){
	asmv("outw %%ax, %%dx" :: "d" (ad), "a" (v));
}
/* output word */
void Io::outl(u32 ad,u32 v){
	asmv("outl %%eax, %%dx" : : "d" (ad), "a" (v));
}
/* input byte */
u8 Io::inb(u32 ad){
	u8 _v;       \
	asmv("inb %%dx, %%al" : "=a" (_v) : "d" (ad)); \
	return _v;
}
/* input word */
u16	Io::inw(u32 ad){
	u16 _v;			\
	asmv("inw %%dx, %%ax" : "=a" (_v) : "d" (ad));	\
	return _v;
}
/* input word */
u32	Io::inl(u32 ad){
	u32 _v;			\
	asmv("inl %%dx, %%eax" : "=a" (_v) : "d" (ad));	\
	return _v;
}

/* renvoie la position x du curseur */
u32	Io::getX(){
	return (u32)x;
}

/* renvoie la position y du curseur */
u32	Io::getY(){
	return (u32)y;
}

/* x86 scroll up screen */
void Io::scrollup(unsigned int n)
{
		unsigned char *video, *tmp;

		for (video = (unsigned char *) real_screen;
		     video < (unsigned char *) SCREENLIM; video += 2) {
			tmp = (unsigned char *) (video + n * 160);

			if (tmp < (unsigned char *) SCREENLIM) {
				*video = *tmp;
				*(video + 1) = *(tmp + 1);
			} else {
				*video = 0;
				*(video + 1) = 0x07;
			}
		}

		y -= n;
		if (y < 0)
			y = 0;
}

/* sauvegarde la memoire video */
void Io::save_screen(){
	memcpy(screen,(char*)RAMSCREEN,SIZESCREEN);
	real_screen=(char*)screen;
}

/* charge la memoire video */
void Io::load_screen(){
	memcpy((char*)RAMSCREEN,screen,SIZESCREEN);
	real_screen=(char*)RAMSCREEN;
}

/* switch tty io */
void Io::switchtty(){
	current_io->save_screen();
	load_screen();
	last_io=current_io;
	current_io=this;
}

/* put a byte on screen */
void Io::putc(char c){
	kattr = 0x07;
	unsigned char *video;
	video = (unsigned char *) (real_screen+ 2 * x + 160 * y);
	if (c == 10) {			
		x = 0;
		y++;
	} else if (c == 8) {	
		if (x) {
				*(video + 1) = 0x0;
			x--;
		}
	} else if (c == 9) {	
		x = x + 8 - (x % 8);
	} else if (c == 13) {	
		x = 0;
	} else {		
			*video = c;
			*(video + 1) = kattr;

		x++;
		if (x > 79) {
			x = 0;
			y++;
		}
	}
			if (y > 24)
				scrollup(y - 24);
}

/* change colors */
void Io::setColor(char fcol,char bcol){
	fcolor=fcol;
	bcolor=bcol;
}

/* change cursor position */
void Io::setXY(char xc,char yc){
	x=xc;
	y=yc;
}

/* clear screen */
void Io::clear(){
	x=0;
	y=0;
	memset((char*)RAMSCREEN,0,SIZESCREEN);
}

/* put a string in screen */
void Io::print(const char *s, ...){
	va_list ap;

	char buf[16];
	int i, j, size, buflen, neg;

	unsigned char c;
	int ival;
	unsigned int uival;

	va_start(ap, s);

	while ((c = *s++)) {
		size = 0;
		neg = 0;

		if (c == 0)
			break;
		else if (c == '%') {
			c = *s++;
			if (c >= '0' && c <= '9') {
				size = c - '0';
				c = *s++;
			}

			if (c == 'd') {
				ival = va_arg(ap, int);
				if (ival < 0) {
					uival = 0 - ival;
					neg++;
				} else
					uival = ival;
				itoa(buf, uival, 10);

				buflen = strlen(buf);
				if (buflen < size)
					for (i = size, j = buflen; i >= 0;
					     i--, j--)
						buf[i] =
						    (j >=
						     0) ? buf[j] : '0';

				if (neg)
					print("-%s", buf);
				else
					print(buf);
			}
			 else if (c == 'u') {
				uival = va_arg(ap, int);
				itoa(buf, uival, 10);

				buflen = strlen(buf);
				if (buflen < size)
					for (i = size, j = buflen; i >= 0;
					     i--, j--)
						buf[i] =
						    (j >=
						     0) ? buf[j] : '0';

				print(buf);
			} else if (c == 'x' || c == 'X') {
				uival = va_arg(ap, int);
				itoa(buf, uival, 16);

				buflen = strlen(buf);
				if (buflen < size)
					for (i = size, j = buflen; i >= 0;
					     i--, j--)
						buf[i] =
						    (j >=
						     0) ? buf[j] : '0';

				print("0x%s", buf);
			} else if (c == 'p') {
				uival = va_arg(ap, int);
				itoa(buf, uival, 16);
				size = 8;

				buflen = strlen(buf);
				if (buflen < size)
					for (i = size, j = buflen; i >= 0;
					     i--, j--)
						buf[i] =
						    (j >=
						     0) ? buf[j] : '0';

				print("0x%s", buf);
			} else if (c == 's') {
				print((char *) va_arg(ap, int));
			} 
		} else
			putc(c);
	}

	return;
}

/* put a byte on the console */
void Io::putctty(char c){
	if (keystate==BUFFERED){
		if (c == 8) {		/* backspace */
			if (keypos>0) {
				inbuf[keypos--] = 0;
			}
		}
		else if (c == 10) {	/* newline */
			inbuf[keypos++] = c;
			inbuf[keypos] = 0; 
			inlock = 0;
			keypos = 0;
		}
		else {
			inbuf[keypos++] = c; 
		}
	}
	else if (keystate==GETCHAR){
		inbuf[0]=c;
		inbuf[1]=0;
		inlock = 0;
		keypos = 0;
	}
}

/* read a string in the console */
u32 Io::read(char* buf,u32 count){
	if (count>1){
		keystate=BUFFERED;
	}
	else{	//getchar
		keystate=GETCHAR;
	}
	asm("sti");
	inlock=1;
	while (inlock == 1);
	asm("cli");
	strncpy(buf,inbuf,count);
	return strlen(buf);
}