
#ifndef ALLOC_H
#define ALLOC_H


extern "C" {
	void *ksbrk(int);
	void *kmalloc(unsigned long);
	void kfree(void *);
}

#endif
