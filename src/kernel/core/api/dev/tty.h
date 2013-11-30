#ifndef __API_TTY__
#define __API_TTY__

#include <api/dev/keyboard.h>

#define TTY_NAME_LEN	16

//tty info
struct tty_info_static{
	char			name[TTY_NAME_LEN];
	char			state;
	char			type;
	unsigned int	flags;
};

struct tty_info_moving{
	unsigned int	x;
	unsigned int	y;
	unsigned int	attrf;
	unsigned int	attrb;
};


//tty type
enum {
    TTY_TYPE_IOSTD=0,
	TTY_TYPE_SERIAL=1,
	TTY_TYPE_SCREEN=2,
	TTY_TYPE_VIRTUAL=3,
	TTY_TYPE_GUI=4
};

//tty state
enum {
    TTY_STATE_RUN=0,
	TTY_STATE_SWITCH=1,
	TTY_STATE_ERROR=2,
	TTY_STATE_PAUSE=3
};


enum TTY_Colour
{
	Black       =0,
	Blue        =1,
	Green       =2,
	Cyan        =3,
	Red         =4,
	Magenta     =5,
	Orange      =6,
	LightGrey   =7,
	DarkGrey    =8,
	LightBlue   =9,
	LightGreen  =10,
	LightCyan   =11,
	LightRed    =12,
	LightMagenta=13,
	Yellow      =14,
	White       =15
};
		  
//iotcl
#define API_TTY_SWITCH_SCREEN	0xff52
#define API_TTY_CLEAR_SCREEN	0xff53
#define API_TTY_GET_SINFO		0xff54
#define API_TTY_GET_MINFO		0xff55
#define API_TTY_SET_MINFO		0xff56

#endif
