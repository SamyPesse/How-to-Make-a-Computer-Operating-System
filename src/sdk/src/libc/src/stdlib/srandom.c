
 

#include <stdlib.h>

extern unsigned int _seed;

void srandom(unsigned int seed){
    _seed = seed;
}
