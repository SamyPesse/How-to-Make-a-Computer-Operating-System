
 
#ifndef _GETOPT_H_
#define _GETOPT_H_

typedef struct option {
    const char *name;
    int has_arg;
    int* flag;
    int val;
} option_t ;

#define no_argument         0
#define required_argument   1
#define optional_argument   2


extern char *optarg;
extern int optind, opterr, optopt;

int getopt( int argc, char* const * argv, const char* opstring );

int getopt_long( int argc, char* const * argv, const char* shortopts,
                 const struct option* longopts, int* longind );

int getopt_long_only( int argc, char* const * argv,
                      const char* shortopts, const struct option* longopts, int* longind );

#endif // _GETOPT_H_
