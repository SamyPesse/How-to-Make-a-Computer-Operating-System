
 

#include <stdlib.h>

extern unsigned int _seed2;

void srand(unsigned int seed){
    _seed2 = seed;
}
