
 
#include <stdlib.h>
#include <stdio.h>

#define MALLOC_MINSIZE	16
#define PAGESIZE	4096

struct malloc_header {
	unsigned long size:31;	/* taille totale de l'enregistrement */
	unsigned long used:1;
} __attribute__ ((packed));


extern char *b_heap;
extern char *e_heap;



char *b_heap = 0;	/* pointe sur le debut du heap */
char *e_heap = 0;		/* pointe sur le sommet du heap */

void* sbrk( int increment );

void* malloc(unsigned long size)
{
	unsigned long realsize;		/* taille totale de l'enregistrement */
	unsigned long i;
	struct malloc_header *bl, *newbl;

	realsize = sizeof(struct malloc_header) + size;
	if ((i = realsize % MALLOC_MINSIZE)) {
		realsize = realsize - i + MALLOC_MINSIZE;
	}

	/* 
	 * On recherche un bloc libre de 'size' octets en parcourant tous les
	 * blocs du heap a partir du debut
	 */
	if (b_heap == 0) {	/* Initialisation du heap */
		if ((b_heap = sbrk(realsize)) == (char*) -1) 
			return (char*) -1;

		e_heap = b_heap + realsize;;

		bl = (struct malloc_header *) b_heap;
		bl->size = realsize;
		bl->used = 0;
	}
	else {
		bl = (struct malloc_header *) b_heap;

		while (bl->used || bl->size < realsize) {
			bl = (struct malloc_header *) ((char *) bl + bl->size);

			if (bl == (struct malloc_header *) e_heap) {
				if ((int)(e_heap = sbrk(realsize)) < 0) {
					return (char*) -1;
				}
				else {
					bl = (struct malloc_header *) e_heap;
					bl->size = realsize;
					bl->used = 0;
					e_heap += realsize;
				}
			} else if (bl > (struct malloc_header *) e_heap) {
				return (char *) -1;	/* BUG ! */ 
			}
		}
	}

	/* 
	 * On a trouve un bloc libre dont la taille est >= 'size'
	 * On fait de sorte que chaque bloc ait une taille minimale
	 */
	if (bl->size - realsize < MALLOC_MINSIZE) {
		bl->used = 1;
	} else {
		newbl = (struct malloc_header *) ((char *) bl + realsize);
		newbl->size = bl->size - realsize;
		newbl->used = 0;

		bl->size = realsize;
		bl->used = 1;
	}
	
	/* retourne un pointeur sur la zone de donnees */
	return (char *) bl + sizeof(struct malloc_header);
}
	

void free(void *v_addr)
{
	struct malloc_header *bl, *nextbl;

	/* Calcul du debut du bloc */
	bl = (struct malloc_header *) (v_addr - sizeof(struct malloc_header));

	/* 
	 * On merge le bloc nouvellement libere avec le bloc suivant ci celui-ci
	 * est aussi libre
	 */
	while ((nextbl = (struct malloc_header *) ((char *) bl + bl->size))
             && nextbl < (struct malloc_header *) e_heap
	     && nextbl->used == 0) 
			bl->size += nextbl->size;

	/* On libere le bloc alloue */
	bl->used = 0;
}


void* realloc(void* ptr,size_t nsize)
{
	if (ptr==0){
		return malloc(nsize);
	}
	else if (nsize==0)
		return ptr;
		
	struct malloc_header *bl=ptr-sizeof(struct malloc_header);
	unsigned long size=bl->size;
	void *newptr=malloc(size+nsize);
	memcpy(newptr,ptr,size);
	free(ptr);
	return newptr;
}
	
void* calloc(size_t n1,size_t n2){
	return malloc(n1*n2);
}
