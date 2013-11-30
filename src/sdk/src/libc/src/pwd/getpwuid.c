
 

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

passwd_myos* myos_user_getID(int id);


struct passwd* getpwuid( uid_t uid ) {

	passwd_myos* pass=myos_user_getID(uid);
	if (pass==NULL)
		return NULL;
	
	build_tmp_passwd();
	return &__tmp_passwd;
}
