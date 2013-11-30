
 

#include <stdarg.h>
#include <stdio.h>
#include <unistd.h>

int putc( int c, FILE* stream ) {
    return fputc( c, stream );
}



int 	support_vfprintf(FILE* stream, const char* format, va_list ap);

int vfprintf(FILE* stream, const char* format, va_list arg)
{
	return support_vfprintf( stream, format, arg );
}

int printf(const char* format, ...)
{
	int rc;
	va_list ap;
	va_start(ap, format);
		rc = vfprintf( stdout, format, ap );
	va_end(ap);
  return rc;
}


int fprintf(FILE*stream,const char* format, ...)
{
	int rc;
	va_list ap;
	va_start(ap, format);
		rc = vfprintf(stream, format, ap );
	va_end(ap);
  return rc;
}
