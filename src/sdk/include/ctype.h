

#ifndef _CTYPE_H_
#define _CTYPE_H_

int isupper( int c );
int islower( int c );
int isalpha( int c );
int isdigit( int c );
int isxdigit( int c );
int isalnum( int c );
int isblank( int c );
int isspace( int c );
int isprint( int c );
int iscntrl( int c );
int isgraph( int c );
int ispunct( int c );
int isascii( int c );

int tolower( int c );
int toupper( int c );

typedef struct {
	long quot;   
	long rem;  
}ldiv_t;

typedef struct {
	int quot;
	int rem;   
}div_t;

div_t div ( int numerator, int denominator );
ldiv_t ldiv ( long numerator, long denominator );




#endif // _CTYPE_H_
