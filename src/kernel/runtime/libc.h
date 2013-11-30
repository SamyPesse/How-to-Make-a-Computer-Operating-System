
#ifndef LIBC_H
#define LIBC_H

#include <stdarg.h>

extern "C" {
	void 	itoa(char *buf, unsigned long int n, int base);
	
	void *	memset(char *dst,char src, int n);
	void *	memcpy(char *dst, char *src, int n);
	
	
	int 	strlen(char *s);
	int 	strcmp(const char *dst, char *src);
	int 	strcpy(char *dst,const char *src);
	void 	strcat(void *dest,const void *src);
	char *	strncpy(char *destString, const char *sourceString,int maxLength);
	int 	strncmp( const char* s1, const char* s2, int c );
}

#endif
