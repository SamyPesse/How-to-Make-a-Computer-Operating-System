
 
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h> /* NULL */

#include <getopt.h>
#include "getopt_int.h"

int getopt_long( int argc, char* const * argv, const char* shortopts,
                 const struct option* longopts, int* longind ){
    return _getopt_internal (argc, argv, shortopts, longopts, longind, 0);
}
