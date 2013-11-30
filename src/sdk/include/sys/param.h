

#ifndef _SYS_PARAM_H_
#define _SYS_PARAM_H_

#include <limits.h>

#undef MIN
#define MIN(a,b) ((a)<(b)?(a):(b))

#undef MAX
#define MAX(a,b) ((a)>(b)?(a):(b))

#define MAXPATHLEN PATH_MAX

#endif // _SYS_PARAM_H_
