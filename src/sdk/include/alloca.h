
 

#ifndef _ALLOCA_H_
#define _ALLOCA_H_

#undef alloca
#define alloca(size) __builtin_alloca(size)

#endif /* _ALLOCA_H_ */
