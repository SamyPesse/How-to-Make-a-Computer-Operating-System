
 

#ifndef _PWD_H_
#define _PWD_H_

#include <sys/types.h>

struct passwd {
    char* pw_name;
    char* pw_passwd;
    uid_t pw_uid;
    gid_t pw_gid;
    char* pw_gecos;
    char* pw_dir;
    char* pw_shell;
};

struct passwd* getpwnam( const char* name );
struct passwd* getpwent( void );
struct passwd* getpwuid( uid_t uid );

void setpwent( void );
void endpwent( void );

#endif /* _PWD_H_ */
