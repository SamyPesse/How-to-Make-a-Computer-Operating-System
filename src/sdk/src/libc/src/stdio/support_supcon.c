
#include <string.h>
#include <stdio.h>

// ---------------- LENGTH OF NUMBERS AND STRINGS ---

int  supcon_leni(int num)
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


int  supcon_lenui(unsigned int p)
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

int  supcon_lenp(unsigned int p)
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

int  supcon_lenx( unsigned int  p )
{
  return (supcon_lenp( p ));
}



// ---------------------- USEFUL STUFF ---------------------------------

void supcon_puts( unsigned char *c )
{
	fputs((const char *)c,stdout);
}

void supcon_putc( unsigned char c )
{
	char buffer[2];
		 buffer[0] = c;
		 buffer[1] = 0;

	fputs((const char *)buffer,stdout);
}


void  supcon_puti( int num )
{
  int sign;
  int temp;
  char buffer[ 128 ];	// You're generous. 
  int position = 126;

  // Short circuit unnecessary work.
  if ( num == 0 ) 
  {
	fputs("0",stdout);
	return;
  }


  // Prepare to do work.
  if ( num < 0 )
  {
	sign = 1;
	temp = -num;
  }
  else
  {
	sign = 0;
	temp = num;
  }
  

  buffer[127] = 0;
  
  // Now reduce it.
  while ( temp > 0 )
  {
	buffer[ position-- ] = '0' + (temp % 10);
	temp = temp / 10;
  }
		  
  if ( sign == 1 ) buffer[ position-- ] = '-';
  
  // Now print it.
  fputs(buffer + position + 1 ,stdout);
}

void  supcon_putui( unsigned int num )
{
  char buffer[ 128 ];	// You're generous. 
  int position = 126;
  unsigned int temp = num;

  // Short circuit unnecessary work.
  if ( num == 0 ) 
  {
	  fputs("0",stdout);
	return;
  }

  buffer[127] = 0;
  
  // Now reduce it.
  while ( temp > 0 )
  {
	buffer[ position-- ] = '0' + (temp % 10);
	temp = temp / 10;
  }
		  
  // Now print it.
  fputs(buffer + position + 1 ,stdout);
}


void  supcon_putp( unsigned int num, char offset )
{
  char buffer[ 128 ];	// You're generous. 
  int position = 126;
  unsigned int temp = num;
  int value;

  // Short circuit unnecessary work.
  if ( num == 0 ) 
  {
	fputs("0",stdout);
	return;
  }

  buffer[127] = 0;
  
  // Now reduce it.
  while ( temp > 0 )
  {
	value = temp % 16;
	if ( value < 10 ) buffer[ position-- ] = '0' + value;
				else  buffer[ position-- ] = offset - 10 + value;	
	temp = temp / 16;
  }
		  
  // Now print it.
    fputs(buffer + position + 1 ,stdout);

}

void  supcon_putx( unsigned int num )
{
   supcon_putp( num, 'a' );
}

void  supcon_putX( unsigned int num )
{
   supcon_putp( num, 'A' );
}



