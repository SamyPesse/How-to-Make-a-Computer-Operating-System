
 

#ifndef _TERMIOS_H_
#define _TERMIOS_H_

/*
 * Number of control characters.
 */

#define NCCS 19

/*
 * Control characters.
 */

#define VINTR     0
#define VQUIT     1
#define VERASE    2
#define VKILL     3
#define VEOF      4
#define VTIME     5
#define VMIN      6
#define VSWTC     7
#define VSTART    8
#define VSTOP     9
#define VSUSP    10
#define VEOL     11
#define VREPRINT 12
#define VDISCARD 13
#define VWERASE  14
#define VLNEXT   15
#define VEOL2    16

#define IGNBRK  0000001
#define BRKINT  0000002
#define IGNPAR  0000004
#define PARMRK  0000010
#define INPCK   0000020
#define ISTRIP  0000040
#define INLCR   0000100
#define IGNCR   0000200
#define ICRNL   0000400
#define IUCLC   0001000
#define IXON    0002000
#define IXANY   0004000
#define IXOFF   0010000
#define IMAXBEL 0020000

#define  B0       0000000
#define  B50      0000001
#define  B75      0000002
#define  B110     0000003
#define  B134     0000004
#define  B150     0000005
#define  B200     0000006
#define  B300     0000007
#define  B600     0000010
#define  B1200    0000011
#define  B1800    0000012
#define  B2400    0000013
#define  B4800    0000014
#define  B9600    0000015
#define  B19200   0000016
#define  B38400   0000017
#define CSIZE     0000060
#define   CS5     0000000
#define   CS6     0000020
#define   CS7     0000040
#define   CS8     0000060
#define CSTOPB    0000100
#define CREAD     0000200
#define PARENB    0000400
#define PARODD    0001000
#define HUPCL     0002000
#define CLOCAL    0004000
#define  B57600   0010001
#define  B115200  0010002
#define  B230400  0010003
#define  B460800  0010004
#define  B500000  0010005
#define  B576000  0010006
#define  B921600  0010007
#define  B1000000 0010010
#define  B1152000 0010011
#define  B1500000 0010012
#define  B2000000 0010013
#define  B2500000 0010014
#define  B3000000 0010015
#define  B3500000 0010016
#define  B4000000 0010017

#define ISIG    0000001
#define ICANON  0000002
#define XCASE   0000004
#define ECHO    0000010
#define ECHOE   0000020
#define ECHOK   0000040
#define ECHONL  0000100
#define NOFLSH  0000200
#define TOSTOP  0000400
#define ECHOCTL 0001000
#define ECHOPRT 0002000
#define ECHOKE  0004000
#define FLUSHO  0010000
#define PENDIN  0040000
#define IEXTEN  0100000

#define OPOST   0000001
#define OLCUC   0000002
#define ONLCR   0000004
#define OCRNL   0000010
#define ONOCR   0000020
#define ONLRET  0000040
#define OFILL   0000100
#define OFDEL   0000200

/* tcflow() and TCXONC use these */

#define TCOOFF          0
#define TCOON           1
#define TCIOFF          2
#define TCION           3

/* tcflush() and TCFLSH use these */

#define TCIFLUSH        0
#define TCOFLUSH        1
#define TCIOFLUSH       2

/* tcsetattr uses these */

#define TCSANOW         0
#define TCSADRAIN       1
#define TCSAFLUSH       2

/* 0x54 is just a magic number to make these relatively unique ('T') */

#define TCGETS          0x5401
#define TCSETS          0x5402 /* Clashes with SNDCTL_TMR_START sound ioctl */
#define TCSETSW         0x5403
#define TCSETSF         0x5404
#define TCGETA          0x5405
#define TCSETA          0x5406
#define TCSETAW         0x5407
#define TCSETAF         0x5408
#define TCSBRK          0x5409
#define TCXONC          0x540A
#define TCFLSH          0x540B
#define TIOCEXCL        0x540C
#define TIOCNXCL        0x540D
#define TIOCSCTTY       0x540E
#define TIOCGPGRP       0x540F
#define TIOCSPGRP       0x5410
#define TIOCOUTQ        0x5411
#define TIOCSTI         0x5412
#define TIOCGWINSZ      0x5413
#define TIOCSWINSZ      0x5414
#define TIOCMGET        0x5415
#define TIOCMBIS        0x5416
#define TIOCMBIC        0x5417
#define TIOCMSET        0x5418
#define TIOCGSOFTCAR    0x5419
#define TIOCSSOFTCAR    0x541A
#define FIONREAD        0x541B
#define TIOCINQ         FIONREAD
#define TIOCLINUX       0x541C
#define TIOCCONS        0x541D
#define TIOCGSERIAL     0x541E
#define TIOCSSERIAL     0x541F
#define TIOCPKT         0x5420
#define FIONBIO         0x5421
#define TIOCNOTTY       0x5422
#define TIOCSETD        0x5423
#define TIOCGETD        0x5424

#define cfgetispeed(tio)      ((tio)->c_ispeed)
#define cfgetospeed(tio)      ((tio)->c_ospeed)
#define cfsetispeed(tio, spd) ((tio)->c_ispeed = (spd))
#define cfsetospeed(tio, spd) ((tio)->c_ospeed = (spd))

typedef unsigned char cc_t;
typedef unsigned int speed_t;
typedef unsigned int tcflag_t;

struct termios {
    tcflag_t c_iflag;
    tcflag_t c_oflag;
    tcflag_t c_cflag;
    tcflag_t c_lflag;
    cc_t c_line;
    cc_t c_cc[ NCCS ];
    speed_t c_ispeed;
    speed_t c_ospeed;
};

struct winsize {
    unsigned short ws_row;
    unsigned short ws_col;
};

int tcflow( int fd, int action );
int tcflush( int fd, int queue_selector );
int tcgetattr( int fd, struct termios* tio );
int tcsetattr( int fd, int optional_actions, const struct termios* tio );

#endif // _TERMIOS_H_
