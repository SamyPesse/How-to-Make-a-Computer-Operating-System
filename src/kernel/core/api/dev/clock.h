#ifndef __API_CLOCK__
#define __API_CLOCK__

typedef unsigned int clock_d;

struct clock_info{
	clock_d		h;
	clock_d		m;
	clock_d		s;
	
	clock_d		day;
	clock_d		month;
	clock_d		year;
};

#define API_CLOCK_GET_INFO		0x6122

#endif
