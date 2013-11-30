
 
#ifndef _GETOPT_INT_H_
#define _GETOPT_INT_H_

struct _getopt_data
{
  int optind;
  int opterr;
  int optopt;
  char *optarg;

  int __initialized;

  char *__nextchar;
  enum
    {
      REQUIRE_ORDER, PERMUTE, RETURN_IN_ORDER
    } __ordering;

  int __posixly_correct;

  int __first_nonopt;
  int __last_nonopt;

  int __nonoption_flags_max_len;
  int __nonoption_flags_len;
};

#define _GETOPT_DATA_INITIALIZER        { 1, 1 }

extern int _getopt_internal (int ___argc, char *const *___argv,
                 const char *__shortopts,
                     const struct option *__longopts, int *__longind,
                 int __long_only);

extern int _getopt_internal_r (int ___argc, char *const *___argv,
                               const char *__shortopts,
                               const struct option *__longopts, int *__longind,
                               int __long_only, struct _getopt_data *__data);

extern int _getopt_long_r (int ___argc, char *const *___argv,
                           const char *__shortopts,
                           const struct option *__longopts, int *__longind,
                           struct _getopt_data *__data);

extern int _getopt_long_only_r (int ___argc, char *const *___argv,
                                const char *__shortopts,
                                const struct option *__longopts,
                                int *__longind,
                                struct _getopt_data *__data);
#endif
