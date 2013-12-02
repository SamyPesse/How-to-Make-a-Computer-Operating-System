#include <os.h>

extern "C" {
	char *kern_heap;
	list_head kern_free_vm;
	u32 *pd0 = (u32 *) KERN_PDIR;			/* kernel page directory */
	char *pg0 = (char *) 0;					/* kernel page 0 (4MB) */
	char *pg1 = (char *) KERN_PG_1;			/* kernel page 1 (4MB) 0x400000*/
	char *pg1_end = (char *) KERN_PG_1_LIM;	/* limite de la page 1 0x800000*/
	u8 mem_bitmap[RAM_MAXPAGE / 8];			/* bitmap allocation de pages (1 Go) */

	u32 kmalloc_used = 0;
	
	
	/*
	 * Parcours le bitmap a la recherche d'une page libre et la marque
	 * comme utilisee avant de retourner son adresse physique.
	 */
	char* get_page_frame(void)
	{
		int byte, bit;
		int page = -1;

		for (byte = 0; byte < RAM_MAXPAGE / 8; byte++)
			if (mem_bitmap[byte] != 0xFF)
				for (bit = 0; bit < 8; bit++)
					if (!(mem_bitmap[byte] & (1 << bit))) {
						page = 8 * byte + bit;
						set_page_frame_used(page);
						return (char *) (page * PAGESIZE);
					}
		return (char *) -1;
	}


	/* 
	 * Recherche une page virtuelle libre dans l'espace d'adresses virtuelles du
	 * noyau. La fonction demande ensuite une page physique libre a associer.
	 * NOTE: ces pages sont dans l'espace d'adressage du noyau. Celui-ci est mis a
	 * jour.
	 */
	page* get_page_from_heap(void)
	{
		page *pg;
		vm_area *area;
		char *v_addr, *p_addr;

		/* Prend une page physique libre */
		p_addr = get_page_frame();
		if ((int)(p_addr) < 0) {
			io.print ("PANIC: get_page_from_heap(): no page frame available. System halted !\n");
		}

		/* Verifie si il y a une page virtuelle libre */
		if (list_empty(&kern_free_vm)) {
			io.print ("PANIC: get_page_from_heap(): not memory left in page heap. System halted !\n");
		}

		/* Prend la premiere page virtuelle libre de disponible */
		area = list_first_entry(&kern_free_vm, vm_area, list);
		v_addr = area->vm_start;

		/* Met a jour la liste de pages libres dans l'espace virtuel du noyau */
		area->vm_start += PAGESIZE;
		if (area->vm_start == area->vm_end) {
			list_del(&area->list);
			kfree(area);
		}

		/* Met a jour l'espace d'adressage du noyau */
		pd0_add_page(v_addr, p_addr, 0);

		/* Renvoie la page */
		pg = (page*) kmalloc(sizeof(page));
		pg->v_addr = v_addr;
		pg->p_addr = p_addr;
		pg->list.next = 0;
		pg->list.prev = 0;

		return pg;
	}

	int release_page_from_heap(char *v_addr)
	{
		struct vm_area *next_area, *prev_area, *new_area;
		char *p_addr;

		/* Retrouve la page frame associee a v_addr et la libere */
		p_addr = get_p_addr(v_addr);
		if (p_addr) {
			release_page_frame(p_addr);
		}
		else {
			io.print("WARNING: release_page_from_heap(): no page frame associated with v_addr %x\n", v_addr);
			return 1;
		}

		/* Met a jour le repertoire de pages */
		pd_remove_page(v_addr);

		/* Met a jour la liste d'adresses virtuelles libres */
		list_for_each_entry(next_area, &kern_free_vm, list) {
			if (next_area->vm_start > v_addr)
				break;
		}

		prev_area = list_entry(next_area->list.prev, struct vm_area, list);
		
		if (prev_area->vm_end == v_addr) {
			prev_area->vm_end += PAGESIZE;
			if (prev_area->vm_end == next_area->vm_start) {
				prev_area->vm_end = next_area->vm_end;
				list_del(&next_area->list);
				kfree(next_area);
			}
		}
		else if (next_area->vm_start == v_addr + PAGESIZE) {
			next_area->vm_start = v_addr;
		}
		else if (next_area->vm_start > v_addr + PAGESIZE) {
			new_area = (struct vm_area*) kmalloc(sizeof(struct vm_area));
			new_area->vm_start = v_addr;
			new_area->vm_end = v_addr + PAGESIZE;
			list_add(&new_area->list, &prev_area->list);
		}
		else {
			io.print ("\nPANIC: release_page_from_heap(): corrupted linked list. System halted !\n");
			asm("hlt");
		}

		return 0;
	}




	/* 
	 * Initialise le bitmap memoire et cree le repertoire de pages du kernel.
	 * Utilise un identity mapping tel que vaddr = paddr sur 4Mo 
	 */
	void Memory_init(u32 high_mem)
	{
		int pg, pg_limit;
		unsigned long i;
		struct vm_area *p;
		struct vm_area *pm;

		/* Numero de la derniere page */
		pg_limit = (high_mem * 1024) / PAGESIZE;

		/* Initialisation du bitmap de pages physiques */
		for (pg = 0; pg < pg_limit / 8; pg++)
			mem_bitmap[pg] = 0;

		for (pg = pg_limit / 8; pg < RAM_MAXPAGE / 8; pg++)
			mem_bitmap[pg] = 0xFF;

		/* Pages reservees pour le noyau */
		for (pg = PAGE(0x0); pg < (int)(PAGE((u32) pg1_end)); pg++) {
			set_page_frame_used(pg);
		}

		/* Initialisation du repertoire de pages */
		pd0[0] = ((u32) pg0 | (PG_PRESENT | PG_WRITE | PG_4MB));
		pd0[1] = ((u32) pg1 | (PG_PRESENT | PG_WRITE | PG_4MB));
		for (i = 2; i < 1023; i++)
			pd0[i] =
			    ((u32) pg1 + PAGESIZE * i) | (PG_PRESENT | PG_WRITE);

		// Page table mirroring magic trick ! 
		pd0[1023] = ((u32) pd0 | (PG_PRESENT | PG_WRITE));


		/* Passe en mode pagination */
		asm("	mov %0, %%eax \n \
			mov %%eax, %%cr3 \n \
			mov %%cr4, %%eax \n \
			or %2, %%eax \n \
			mov %%eax, %%cr4 \n \
			mov %%cr0, %%eax \n \
			or %1, %%eax \n \
			mov %%eax, %%cr0"::"m"(pd0), "i"(PAGING_FLAG), "i"(PSE_FLAG));

		
		/* Initialisation du heap du noyau utilise par kmalloc */
		kern_heap = (char *) KERN_HEAP;
		ksbrk(1);

		/* Initialisation de la liste d'adresses virtuelles libres */
		p = (struct vm_area*) kmalloc(sizeof(struct vm_area));
		p->vm_start = (char*) KERN_PG_HEAP;
		p->vm_end = (char*) KERN_PG_HEAP_LIM;
		INIT_LIST_HEAD(&kern_free_vm);
		list_add(&p->list, &kern_free_vm);

		arch.initProc();

		return;
	}

	/*
	 * Cree et initialise un rep. de pages pour une tache
	 */
	struct page_directory *pd_create(void)
	{
		struct page_directory *pd;
		u32 *pdir;
		int i;

		/* Prend et initialise une page pour le Page Directory */
		pd = (struct page_directory *) kmalloc(sizeof(struct page_directory));
		pd->base = get_page_from_heap();

		/* 
		 * Espace kernel. Les v_addr < USER_OFFSET sont adressees par la table
		 * de pages du noyau (pd0[]).
		 */
		pdir = (u32 *) pd->base->v_addr;
		for (i = 0; i < 256; i++)
			pdir[i] = pd0[i];

		/* Espace utilisateur */
		for (i = 256; i < 1023; i++)
			pdir[i] = 0;

		/* Page table mirroring magic trick !... */
		pdir[1023] = ((u32) pd->base->p_addr | (PG_PRESENT | PG_WRITE));


		/* Mise a jour de la liste des tables de pages de l'espace utilisateur */
		INIT_LIST_HEAD(&pd->pt);

		return pd;
	}

	void page_copy_in_pd(process_st* current,u32 virtadr){
			struct page *pg;
			pg = (struct page *) kmalloc(sizeof(struct page));
			pg->p_addr = get_page_frame();
			/* todo copier le contenus de l'autre page */
			pg->v_addr = (char *) (virtadr & 0xFFFFF000);
			list_add(&pg->list, &current->pglist);
			pd_add_page(pg->v_addr, pg->p_addr, PG_USER, current->pd);
	}


	/*
	 * Cree et initialise un rep. de pages pour une tache en copie d'une autre  (ne marche pas encore )
	 */
	struct page_directory *pd_copy(struct page_directory * pdfather)
	{
		struct page_directory *pd;
		u32 *pdir;
		int i;

		/* Prend et initialise une page pour le Page Directory */
		pd = (struct page_directory *) kmalloc(sizeof(struct page_directory));
		pd->base = get_page_from_heap();

		/* 
		 * Espace kernel. Les v_addr < USER_OFFSET sont adressees par la table
		 * de pages du noyau (pd0[]).
		 */
		pdir = (u32 *) pd->base->v_addr;
		for (i = 0; i < 256; i++)
			pdir[i] = pd0[i];

		/* Espace utilisateur */
		for (i = 256; i < 1023; i++)
			pdir[i] = 0;

		/* Page table mirroring magic trick !... */
		pdir[1023] = ((u32) pd->base->p_addr | (PG_PRESENT | PG_WRITE));


		/* Mise a jour de la liste des tables de pages de l'espace utilisateur */
		INIT_LIST_HEAD(&pd->pt);

		return pd;
	}

	int pd_destroy(struct page_directory *pd)
	{
		struct page *pg;
		struct list_head *p, *n;

		/* Libere les pages correspondant aux tables */
		list_for_each_safe(p, n, &pd->pt) {
			pg = list_entry(p, struct page, list);
			release_page_from_heap(pg->v_addr);
			list_del(p);
			kfree(pg);
		}

		/* Libere la page correspondant au repertoire */
		release_page_from_heap(pd->base->v_addr);
		kfree(pd);

		return 0;
	}

	/* 
	 * Met a jour l'espace d'adressage du noyau.
	 * NOTE : cet espace est commun a tous les repertoires de pages.
	 */
	int pd0_add_page(char *v_addr, char *p_addr, int flags)
	{
		u32 *pde;
		u32 *pte;

		if (v_addr > (char *) USER_OFFSET) {
			io.print("ERROR: pd0_add_page(): %p is not in kernel space !\n", v_addr);
			return 0;
		}

		/* On verifie que la table de page est bien presente */
		pde = (u32 *) (0xFFFFF000 | (((u32) v_addr & 0xFFC00000) >> 20));
		if ((*pde & PG_PRESENT) == 0) {
			//error
		}

		/* Modification de l'entree dans la table de page */
		pte = (u32 *) (0xFFC00000 | (((u32) v_addr & 0xFFFFF000) >> 10));
		*pte = ((u32) p_addr) | (PG_PRESENT | PG_WRITE | flags);
		set_page_frame_used(p_addr);
		return 0;
	}

	/* 
	 * Met a jour le repertoire de pages courant
	 * input:
	 * 	v_addr : adresse lineaire de la page 
	 * 	p_addr : adresse physique de la page allouee 
	 * 	pd     : structure qui doit etre mise a jour avec les pages allouees
	 */
	int pd_add_page(char *v_addr, char *p_addr, int flags, struct page_directory *pd)
	{
		u32 *pde;		/* adresse virtuelle de l'entree du repertoire de pages */
		u32 *pte;		/* adresse virtuelle de l'entree de la table de pages */
		u32 *pt;		/* adresse virtuelle de la table de pages */
		struct page *pg;
		int i;

		//// io.print("DEBUG: pd_add_page(%p, %p, %d)\n", v_addr, p_addr, flags); /* DEBUG */

		/*
		 * La derniere entree du PageDir pointe sur lui-meme.
		 * Les adresses commencant par 0xFFC00000 utilisent cette entree et il
		 * s'ensuite que :
		 * - les 10 bits en 0x003FF000 sont un index dans le PageDir et designent une
		 *   PageTable. Les 12 derniers bits permettent de modifier une entree du PageTable
		 * - l'adresse 0xFFFFF000 designe le PageDir lui-meme
		 */
		pde = (u32 *) (0xFFFFF000 | (((u32) v_addr & 0xFFC00000) >> 20));

		/* 
		 * On cree la table de pages correspondante si elle n'est pas presente
		 */
		if ((*pde & PG_PRESENT) == 0) {

			/* 
			 * Allocation d'une page pour y mettre la table. 
			 */
			pg = get_page_from_heap();

			/* On initialise la nouvelle table de pages */
			pt = (u32 *) pg->v_addr;
			for (i = 1; i < 1024; i++)
				pt[i] = 0;

			/* On ajoute l'entree correspondante dans le repertoire */
			*pde = (u32) pg->p_addr | (PG_PRESENT | PG_WRITE | flags);

			/* On rajoute la nouvelle page dans la structure  passee en parametre */
			if (pd) 
				list_add(&pg->list, &pd->pt);
		}

		pte = (u32 *) (0xFFC00000 | (((u32) v_addr & 0xFFFFF000) >> 10));
		*pte = ((u32) p_addr) | (PG_PRESENT | PG_WRITE | flags);

		return 0;
	}

	int pd_remove_page(char *v_addr)
	{
		u32 *pte;

		if (get_p_addr(v_addr)) {
			pte = (u32 *) (0xFFC00000 | (((u32) v_addr & 0xFFFFF000) >> 10));
			*pte = (*pte & (~PG_PRESENT));
			
			asm("invlpg %0"::"m"(v_addr));
		}

		return 0;
	}

	/*
	 * Retourne l'adresse physique de la page associee a l'adresse virtuelle passee
	 * en argument
	 */
	char *get_p_addr(char *v_addr)
	{
		u32 *pde;		/* adresse virtuelle de l'entree du repertoire de pages */
		u32 *pte;		/* adresse virtuelle de l'entree de la table de pages */

		pde = (u32 *) (0xFFFFF000 | (((u32) v_addr & 0xFFC00000) >> 20));
		if ((*pde & PG_PRESENT)) {
			pte = (u32 *) (0xFFC00000 | (((u32) v_addr & 0xFFFFF000) >> 10));
			if ((*pte & PG_PRESENT))
				return (char *) ((*pte & 0xFFFFF000) + (VADDR_PG_OFFSET((u32) v_addr)));
		}

		return 0;
	}
}

void Vmm::kmap(u32 phy,u32 virt){
	pd0_add_page((char*)phy,(char*)virt,PG_USER);
}

void Vmm::init(u32 high){
	Memory_init(high);
}
