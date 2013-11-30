#include <os.h>


extern "C" {

/* 
 * La fonction memcpy permet de copier n octets de src vers dest.
 * Les adresses sont lineaires.
 */
void *memcpy(char *dst, char *src, int n)
{
	char *p = dst;
	while (n--)
		*dst++ = *src++;
	return p;
}

/*
 * Met un ensemble memoire (dst>>n) à la valeur src
 */
void *memset(char *dst,char src, int n)
{
	char *p = dst;
	while (n--)
		*dst++ = src;
	return p;
}

}

