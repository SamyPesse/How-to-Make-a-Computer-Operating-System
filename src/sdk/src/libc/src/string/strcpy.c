
 

#include <string.h>
#include <stdarg.h>


char* strcpy( char* d, const char* s ) {
    char* tmp = d;

    while ( ( *d++ = *s++ ) != 0 ) ;

    return tmp;
}

int support_vsprintf(char* buffer, const char* format, va_list ap);

int vsprintf(char* s, const char* format, va_list arg)
{
	return support_vsprintf( s, format, arg );
}


int sprintf(char *buffer, const char* format, ...)
{
	int rc;
	va_list ap;
	va_start(ap, format);
		rc = vsprintf( buffer, format, ap );
	va_end(ap);
   return 0;

}

