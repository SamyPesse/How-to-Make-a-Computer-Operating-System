
#ifndef BUFFER_H
#define BUFFER_H


class Buffer
{
	public:
		Buffer(char* n,u32 siz);
		Buffer();
		~Buffer();
		
		void	add(u8* c,u32 s);
		u32	get(u8* c,u32 s);
		void	clear();
		u32		isEmpty();
		
		
		Buffer &operator>>(char *c);
		
		
		u32 	size;
		char*	map;
	
};


#endif
