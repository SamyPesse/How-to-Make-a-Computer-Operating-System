
 

#include <pwd.h>


typedef struct passwd_myos passwd_myos;
struct passwd_myos {
    char name[64];
    char password[64];
    int uid;
    int gid;
    char gecos[64];
    char dir[512];
    char shell[64];
};

extern struct passwd __tmp_passwd;
passwd_myos* myos_user_getN(const char* name);
void build_tmp_passwd();

struct passwd* getpwnam( const char* name ) {

	passwd_myos* pass=myos_user_getN(name);
	if (pass==NULL)
		return NULL;
	
	build_tmp_passwd();
	return &__tmp_passwd;
}
