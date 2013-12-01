## Chapter 5: Base classes for managing x86 architecture

Now that we know how to compile our C++ kernel and boot the binary using GRUB, we can start to do some nice stuffs in C/C++.

#### Printing to the screen console

We are going to use VGA default mode (03h) to display some text to the user. The screen can be directly access using the video memory at 0xB8000. The screen resolution is 80x25 and each caracters in the screen is defined by 2 bytes: one for the caracter and one for the style flag. So the size of the video memory is 4000 = 80*25*2

We add a method **putc** to the IO Class to put a caracter on the screen and update the x,y position.

```
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
```
