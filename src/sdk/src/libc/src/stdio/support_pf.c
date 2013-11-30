

#include <stdarg.h>
#include <stdio.h>
#include <string.h>

int  bufcon_leni(int num);
int  bufcon_lenui(unsigned int p);
int  bufcon_lenp(unsigned int p);
int  bufcon_lenx( unsigned int  p );
int  bufcon_lens( char *s );
char*  bufcon_putc( char *buffer, unsigned char c );
char*  bufcon_puts( char *buffer, char *str );
char*  bufcon_puti( char *buffer, int num );
char*  bufcon_putui( char *buffer, unsigned int num );
char*  bufcon_putp( char *buffer, unsigned int p );
char*  bufcon_putx( char *buffer, unsigned int p );
char*  bufcon_putX( char *buffer, unsigned int p );

void  supcon_putX( unsigned int num );
void  supcon_putx( unsigned int num );
void  supcon_putp( unsigned int num, char offset );
void  supcon_putui( unsigned int num );
void  supcon_puti( int num );
void supcon_putc( unsigned char c );
void supcon_puts( unsigned char *c );
int  supcon_lenx( unsigned int  p );
int  supcon_lenp(unsigned int p);
int  supcon_lenui(unsigned int p);
int  supcon_leni(int num);

 
int printf_buffer(int i)
{
	int j;
	if ( i <= 0 ) return 0;
	for ( j = 0; j < i; j++) supcon_putc(' ');
	return 0;
}


#define STATE_OFF	0
#define STATE_PAD	1

int 	support_vfprintf(FILE* stream, const char* format, va_list ap)
{
	int d, i;
	int index;
	char c,  *s;
	int modifier;
	int state;

	int off_length;
	int pad_length;

	modifier = 0;
	state    = STATE_OFF;
	
	off_length = 0;
	pad_length = 0;

	while (*format)
	{
	  switch(*format++) 
	  {
	     case 's':       
			if (modifier == 0) { supcon_putc(*(format-1)); break; }
			s = va_arg(ap, char*);
			printf_buffer( off_length - strlen(s) );
			supcon_puts((unsigned char*)s);
			modifier = 0;
			off_length = 0;
			pad_length = 0;
			state = STATE_OFF;
			break;
	     case 'd':        
	     case 'i':        
			if (modifier == 0) { supcon_putc(*(format-1)); break; }
			i = va_arg(ap, int);
			printf_buffer( off_length - supcon_leni(i) - pad_length );
			for ( index = 0; index < pad_length - supcon_leni(i); index++)
			  supcon_putc( '0' );
		  
			supcon_puti(i);
			modifier = 0;
			off_length = 0;
			pad_length = 0;
			state = STATE_OFF;
			break;
	     case 'u':        
			if (modifier == 0) { supcon_putc(*(format-1)); break; }
			i = va_arg(ap, int);
			printf_buffer( off_length - supcon_lenui(i) - pad_length );
			for ( index = 0; index < pad_length - supcon_lenui(i); index++)
			  supcon_putc( '0' );
			  
			supcon_putui(i);
			modifier = 0;
			off_length = 0;
			pad_length = 0;
			state = STATE_OFF;
			break;
	     case 'p':         
			if (modifier == 0) { supcon_putc(*(format-1)); break; }
			d = va_arg(ap, int);
			printf_buffer( off_length - supcon_lenp(d) - pad_length );
			for ( index = 0; index < pad_length - supcon_lenp(d); index++ )
			   supcon_putc( '0' );
			   
			supcon_putp(d,'A');
			modifier = 0;
			off_length = 0;
			pad_length = 0;
			state = STATE_OFF;
			break;
	     case 'x':         
			if (modifier == 0) { supcon_putc(*(format-1)); break; }
			d = va_arg(ap, int);
			
			printf_buffer( off_length - supcon_lenx(d) - 2 );
			supcon_puts((unsigned char*)"0x");
			for ( index = 0; index < pad_length-supcon_lenx(d)-2; index++ )
			   supcon_putc( '0' );
	
			supcon_putx(d);
			modifier = 0;
			off_length = 0;
			pad_length = 0;
			state = STATE_OFF;
			break;
	     case 'l':         
			if (modifier == 0) { supcon_putc(*(format-1)); break; }
			break;
	     case 'X':         
			if (modifier == 0) { supcon_putc(*(format-1)); break; }
			d = va_arg(ap, int);
			printf_buffer( off_length - supcon_lenx(d) - 2 );
			supcon_puts((unsigned char*)"0x");
			for ( index = 0; index < pad_length-supcon_lenx(d)-2; index++ )
			   supcon_putc( '0' );
			   
			supcon_putX(d);
			
			modifier = 0;
			off_length = 0;
			pad_length = 0;
			state = STATE_OFF;
			break;
	     case 'c':          
			if (modifier == 0) { supcon_putc(*(format-1)); break; }
			c = (char) va_arg(ap, int);
			printf_buffer( off_length - 1 );
			supcon_putc(c);
			modifier = 0;
			off_length = 0;
			pad_length = 0;
			state = STATE_OFF;
			break;
	     case '%':
			modifier = 1;
			off_length = 0;
			pad_length = 0;
			state = STATE_OFF;
			break;
	     case '.':
			if (modifier == 0) { supcon_putc(*(format-1)); break; }
			if ( state == STATE_PAD ) 
			{
				modifier = 0;
				off_length = 0;
				pad_length = 0;
				state = STATE_OFF;
				break; 
			}
	
			state = STATE_PAD;
			break;
	     
	     case '0':
	     case '1':
	     case '2':
	     case '3':
	     case '4':
	     case '5':
	     case '6':
	     case '7':
	     case '8':
	     case '9':
	   		if ( modifier != 1 )
			{
			  supcon_putc( *(format-1) );
	  	  	  modifier = 0;
			  off_length = 0;
			  pad_length = 0;
			  state = STATE_OFF;
			  break;
			}
			if ( state == STATE_OFF )
			  off_length = off_length * 10 + ((*(format-1)) - '0');
			if ( state == STATE_PAD )
			  pad_length = pad_length * 10 + ((*(format-1)) - '0');
	     		break;

	     default:     
			printf_buffer( off_length - 1 );
			supcon_putc( *(format-1) );
			modifier = 0;
			off_length = 0;
			pad_length = 0;
			state = STATE_OFF;
			break;
	 }
	}
   return 0;
}

// ---------------------------------


int sprintf_buffer(char *s, int i)
{
	int j;
	if ( i <= 0 ) return 0;
	for ( j = 0; j < i; j++) strcat(s," ");
	return 0;
}

int vsnprintf(char* str, size_t size, const char *format, va_list arg_ptr) {
	return support_vsprintf(str,format,arg_ptr);
}

int snprintf(char *str,size_t size,const char *format,...)
{
  int n;
  va_list arg_ptr;
  va_start(arg_ptr, format);
  n=vsnprintf(str,size,format,arg_ptr);
  va_end (arg_ptr);
  return n;
}

int 	support_vsprintf(char* buffer, const char* format, va_list ap)
{
	int d, i;
	int index;
	char c,  *s;
	int modifier;
	int state;

	int off_length;
	int pad_length;

	modifier = 0;
	state    = STATE_OFF;
	
	off_length = 0;
	pad_length = 0;

	buffer[0] = 0;

	while (*format)
	{
	  switch(*format++) 
	  {
	     case 's':       
		if (modifier == 0) { bufcon_putc( buffer, *(format-1)); break; }
		s = va_arg(ap, char*);
		sprintf_buffer( buffer, off_length - strlen(s) );
		bufcon_puts( buffer, s);
		modifier = 0;
		off_length = 0;
		pad_length = 0;
		state = STATE_OFF;
		break;
	     case 'd':        
	     case 'i':        
		if (modifier == 0) { bufcon_putc( buffer, *(format-1)); break; }
		i = va_arg(ap, int);
		sprintf_buffer( buffer, off_length - supcon_leni(i) - pad_length );
		for ( index = 0; index < pad_length - supcon_leni(i); index++)
		  bufcon_putc( buffer, '0' );
		  
		bufcon_puti(buffer, i);
		modifier = 0;
		off_length = 0;
		pad_length = 0;
		state = STATE_OFF;
		break;
	     case 'u':        
		if (modifier == 0) { bufcon_putc( buffer, *(format-1)); break; }
		i = va_arg(ap, int);
		sprintf_buffer( buffer, off_length - supcon_lenui(i) - pad_length );
		for ( index = 0; index < pad_length - supcon_lenui(i); index++)
		  bufcon_putc( buffer, '0' );
		  
		bufcon_putui( buffer, i);
		modifier = 0;
		off_length = 0;
		pad_length = 0;
		state = STATE_OFF;
		break;
	     case 'p':         
		if (modifier == 0) { bufcon_putc( buffer, *(format-1)); break; }
		d = va_arg(ap, int);
		sprintf_buffer( buffer, off_length - supcon_lenp(d) - pad_length );
		for ( index = 0; index < pad_length - supcon_lenp(d); index++ )
		   bufcon_putc( buffer, '0' );
		   
		bufcon_putp( buffer, d);
		modifier = 0;
		off_length = 0;
		pad_length = 0;
		state = STATE_OFF;
		break;

	     case 'l':         
			if (modifier == 0) { supcon_putc(*(format-1)); break; }
			break;

	     case 'x':         
		if (modifier == 0) { bufcon_putc( buffer, *(format-1)); break; }
		d = va_arg(ap, int);
		
		sprintf_buffer( buffer, off_length - supcon_lenx(d) - 2 );
		/*bufcon_puts(buffer,"0x");
		for ( index = 0; index < pad_length-supcon_lenx(d)-2; index++ )
		   bufcon_putc( buffer, '0' );*/

		bufcon_putx( buffer, d);
		modifier = 0;
		off_length = 0;
		pad_length = 0;
		state = STATE_OFF;
		break;
	     case 'X':         
		if (modifier == 0) { bufcon_putc( buffer, *(format-1)); break; }
		d = va_arg(ap, int);
		sprintf_buffer( buffer, off_length - supcon_lenx(d) - 2 );
		/*bufcon_puts(buffer,"0x");
		for ( index = 0; index < pad_length-supcon_lenx(d)-2; index++ )
		   bufcon_putc( buffer, '0' );*/
		   
		bufcon_putX(buffer,d);
		
		modifier = 0;
		off_length = 0;
		pad_length = 0;
		state = STATE_OFF;
		break;
	     case 'c':          
		if (modifier == 0) { bufcon_putc( buffer, *(format-1)); break; }
		c = (char) va_arg(ap, int);
		sprintf_buffer( buffer, off_length - 1 );
		bufcon_putc(buffer, c);
		modifier = 0;
		off_length = 0;
		pad_length = 0;
		state = STATE_OFF;
		break;
	     case '%':
		modifier = 1;
		off_length = 0;
		pad_length = 0;
		state = STATE_OFF;
		break;
	     case '.':
		if (modifier == 0) { bufcon_putc( buffer, *(format-1)); break; }
		if ( state == STATE_PAD ) 
		{
			modifier = 0;
			off_length = 0;
			pad_length = 0;
			state = STATE_OFF;
			break; 
		}

		state = STATE_PAD;
		break;
	     
	     case '0':
	     case '1':
	     case '2':
	     case '3':
	     case '4':
	     case '5':
	     case '6':
	     case '7':
	     case '8':
	     case '9':
	     		if ( modifier != 1 )
			{
			  bufcon_putc( buffer, *(format-1) );
	  	  	  modifier = 0;
			  off_length = 0;
			  pad_length = 0;
			  state = STATE_OFF;
			  break;
			}
			if ( state == STATE_OFF )
			  off_length = off_length * 10 + ((*(format-1)) - '0');
			if ( state == STATE_PAD )
			  pad_length = pad_length * 10 + ((*(format-1)) - '0');
	     		break;
	     
	     default:     
		sprintf_buffer( buffer, off_length - 1 );
		bufcon_putc( buffer, *(format-1) );
		modifier = 0;
		off_length = 0;
		pad_length = 0;
		state = STATE_OFF;
		break;
	 }
	}
   return 0;
}




 




