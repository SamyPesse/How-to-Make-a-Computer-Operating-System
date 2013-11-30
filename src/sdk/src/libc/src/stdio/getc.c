
 
#include <stdio.h>

int getc( FILE* stream ) {
    return fgetc( stream );
}

int gets(char* buf){
	fgets(buf,512,stdin); 
	return 1;
}
