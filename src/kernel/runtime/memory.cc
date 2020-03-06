#include <os.h>


extern "C" {

/* 
 * The memcpy function allows you to copy n bytes from src to dest.
 * The addresses are linear.
 */
void *memcpy(char *dst, char *src, int n)
{
	char *p = dst;
	while (n--)
		*dst++ = *src++;
	return p;
}

/*
 * Set a memory set (dst >> n) to the value src
 */
void *memset(char *dst,char src, int n)
{
	char *p = dst;
	while (n--)
		*dst++ = src;
	return p;
}

}

