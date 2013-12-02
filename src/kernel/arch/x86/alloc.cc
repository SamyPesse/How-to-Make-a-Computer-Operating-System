#include <os.h>

extern "C" {
		
	/* change memory segment size */
	void *ksbrk(int n)
	{
		struct kmalloc_header *chunk;
		char *p_addr;
		int i;

		if ((kern_heap + (n * PAGESIZE)) > (char *) KERN_HEAP_LIM) {
			io.print
			    ("PANIC: ksbrk(): no virtual memory left for kernel heap !\n");
			return (char *) -1;
		}

		chunk = (struct kmalloc_header *) kern_heap;

		/* Allocation d'une page libre */
		for (i = 0; i < n; i++) {
			p_addr = get_page_frame();
			if ((int)(p_addr) < 0) {
				io.print
				    ("PANIC: ksbrk(): no free page frame available !\n");
				return (char *) -1;
			}

			/* Ajout dans le repertoire de pages */
			pd0_add_page(kern_heap, p_addr, 0);

			kern_heap += PAGESIZE;
		}

		/* Marquage pour kmalloc */
		chunk->size = PAGESIZE * n;
		chunk->used = 0;

		return chunk;
	}

	/* allocate memory block */
	void *kmalloc(unsigned long size)
	{
		if (size==0)
			return 0;
			
		unsigned long realsize;	/* taille totale de l'enregistrement */
		struct kmalloc_header *chunk, *other;

		if ((realsize =
		     sizeof(struct kmalloc_header) + size) < KMALLOC_MINSIZE)
			realsize = KMALLOC_MINSIZE;

		/* 
		 * On recherche un bloc libre de 'size' octets en parcourant le HEAP
		 * kernel a partir du debut
		 */
		chunk = (struct kmalloc_header *) KERN_HEAP;
		while (chunk->used || chunk->size < realsize) {
			if (chunk->size == 0) {
				io.print
				    ("\nPANIC: kmalloc(): corrupted chunk on %x with null size (heap %x) !\nSystem halted\n",
				     chunk, kern_heap);
					 //error
					 asm("hlt");
					 return 0;
			}

			chunk =
			    (struct kmalloc_header *) ((char *) chunk +
						       chunk->size);

			if (chunk == (struct kmalloc_header *) kern_heap) {
				if ((int)(ksbrk((realsize / PAGESIZE) + 1)) < 0) {
					io.print
					    ("\nPANIC: kmalloc(): no memory left for kernel !\nSystem halted\n");
					 asm("hlt");
					return 0;
				}
			} else if (chunk > (struct kmalloc_header *) kern_heap) {
				io.print
				    ("\nPANIC: kmalloc(): chunk on %x while heap limit is on %x !\nSystem halted\n",
				     chunk, kern_heap);
				 asm("hlt");
				return 0;
			}
		}

		/* 
		 * Found free block with size >= 'size'
		 * We limit size block
		 */
		if (chunk->size - realsize < KMALLOC_MINSIZE)
			chunk->used = 1;
		else {
			other =
			    (struct kmalloc_header *) ((char *) chunk + realsize);
			other->size = chunk->size - realsize;
			other->used = 0;

			chunk->size = realsize;
			chunk->used = 1;
		}

		kmalloc_used += realsize;

		/* Return a pointer to the memory area */
		return (char *) chunk + sizeof(struct kmalloc_header);
	}

	/* free memory block */
	void kfree(void *v_addr)
	{
		if (v_addr==(void*)0)
			return;
			
		struct kmalloc_header *chunk, *other;

		/* On libere le bloc alloue */
		chunk =
		    (struct kmalloc_header *) ((u32)v_addr -
					       sizeof(struct kmalloc_header));
		chunk->used = 0;

		kmalloc_used -= chunk->size;

		/* 
		 * Merge free block with next free block
		 */
		while ((other =
			(struct kmalloc_header *) ((char *) chunk + chunk->size))
		       && other < (struct kmalloc_header *) kern_heap
		       && other->used == 0)
			chunk->size += other->size;
	}
}
