

#include <string.h>

/*
 *  This file not a part of the standard C99 library but
 *  I'm keeping the helper functions for printf and
 *  sprintf here.
 *
 *  So this file consists of formatting and printing (to 
 *  screen and to a buffer) of strings and numbers.
 *
 */

// ---------------- LENGTH OF NUMBERS AND STRINGS ---

int  bufcon_leni(int num)
{
  int p;
  int sign;

      if ( num < 0 ) 
      {
        p = -num;
      	sign = 1;
      }
      else
      {
        p = num;
      	sign = 0;
      }
  
	if ( p < 10 ) return sign + 1;
	if ( p < 100 ) return sign + 2;
	if ( p < 1000 ) return sign + 3;
	if ( p < 10000 ) return sign + 4;
	if ( p < 100000 ) return sign + 5;
	if ( p < 1000000 ) return sign + 6;
	if ( p < 10000000 ) return sign + 7;
	if ( p < 100000000 ) return sign + 8;
	if ( p < 1000000000 ) return sign + 9;

  return 10;
}


int  bufcon_lenui(unsigned int p)
{

	if ( p < 10 ) return 1;
	if ( p < 100 ) return 2;
	if ( p < 1000 ) return 3;
	if ( p < 10000 ) return 4;
	if ( p < 100000 ) return 5;
	if ( p < 1000000 ) return 6;
	if ( p < 10000000 ) return 7;
	if ( p < 100000000 ) return 8;
	if ( p < 1000000000 ) return 9;

  return 10;
}

int  bufcon_lenp(unsigned int p)
{
	if ( p < 0x10 ) return 1;
	if ( p < 0x100 ) return 2;
	if ( p < 0x1000 ) return 3;
	if ( p < 0x10000 ) return 4;
	if ( p < 0x100000 ) return 5;
	if ( p < 0x1000000 ) return 6;
	if ( p < 0x10000000 ) return 7;

  return 8;
}

int  bufcon_lenx( unsigned int  p )
{
  return (bufcon_lenp( p ) + 2);
}

int  bufcon_lens( char *s )
{
   int i = 0;
   while ( s[i] != 0 ) i++; 
   return i;
}




// ---------------- BUFFER MANIPULATION -------------

char*  bufcon_putc( char *buffer, unsigned char c )
{
  unsigned char str[2];
   
     str[0] = c;
     str[1] = 0;
     
     strcat( buffer,(const char*)str );
     
  return buffer;
}

char*  bufcon_puts( char *buffer, char *str )
{
  strcat( buffer, str );
  return buffer;
}

char*  bufcon_puti( char *buffer, int num )
{
  unsigned int divisor;
  unsigned int current;
  unsigned int remainder;
  unsigned int found;
 
  if ( num < 0 )
  {
    bufcon_putc( buffer, '-' );
    current = -num;
  }
  else current = num;
 
  divisor = 1000000000;
  found = 0;
  
  while (divisor > 0)
  {
    remainder = current % divisor;
      current = current / divisor;

    if ( current != 0 ) found = 1;
    if ( found   != 0 ) bufcon_putc( buffer, current + '0' );

    divisor = divisor / 10;
    current = remainder;
  }

  if ( found == 0 ) bufcon_putc( buffer, current + '0' );

  return buffer;
}

char*  bufcon_putui( char *buffer, unsigned int num )
{
  unsigned int divisor;
  unsigned int current;
  unsigned int remainder;
  unsigned int found;
 
  current = num;
 
  divisor = 1000000000;
  found = 0;
  
  while (divisor > 0)
  {
    remainder = current % divisor;
      current = current / divisor;

    if ( current != 0 ) found = 1;
    if ( found   != 0 ) bufcon_putc( buffer, current + '0' );

    divisor = divisor / 10;
    current = remainder;
  }

  if ( found == 0 ) bufcon_putc( buffer, current + '0' );

  return buffer;
}


char*  bufcon_putp( char *buffer, unsigned int p )
{
   int offset;
   unsigned char c;
   int found = 0;

   for ( offset = 28; offset >= 0; offset -= 4 )
   {
     c = (p>>offset) & 0xF;
     if ( c != 0 ) found = 1;
     if ( found == 1 )
     {
     	if ( c < 10 ) bufcon_putc( buffer, c + '0' );
     	         else bufcon_putc( buffer, c - 10 + 'a' );
     }
   }
   
   if (found == 0 ) bufcon_putc( buffer, '0' );
   
   return buffer;
}

char*  bufcon_putx( char *buffer, unsigned int p )
{
   int offset;
   unsigned char c;
   int found = 0;

   bufcon_puts( buffer, "0x" );

   for ( offset = 28; offset >= 0; offset -= 4 )
   {
     c = (p>>offset) & 0xF;
     if ( c != 0 ) found = 1;
     if ( found == 1 )
     {
       if ( c < 10 ) bufcon_putc( buffer, c + '0' );
        	else bufcon_putc( buffer, c - 10 + 'a' );
     }
   }
  
   if (found == 0 ) bufcon_putc( buffer, '0' );
  
   return buffer;
}

char*  bufcon_putX( char *buffer, unsigned int p )
{
   int offset;
   unsigned char c;
   int found = 0;

   bufcon_puts( buffer, "0x" );

   for ( offset = 28; offset >= 0; offset -= 4 )
   {
     c = (p>>offset) & 0xF;
     if ( c != 0 ) found = 1;
     if ( found == 1 )
     {
        if ( c < 10 ) bufcon_putc( buffer, c + '0' );
     	         else bufcon_putc( buffer, c - 10 + 'A' );
     }
   }
   
   if (found == 0 ) bufcon_putc( buffer, '0' );
   
   return buffer;
}


