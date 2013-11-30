
 

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

passwd_myos myos_pass;

passwd_myos* myos_user_getN(const char* name){
	int ret=syscall2(68,(uint32_t)name,(uint32_t)&myos_pass);
	if (ret!=0)
		return &myos_pass;
	else
		return NULL;
}

passwd_myos* myos_user_getID(int id){
	int ret=syscall2(69,id,(uint32_t)&myos_pass);
	if (ret!=0)
		return &myos_pass;
	else
		return NULL;
}

int _passwd_db_position = 0;

struct passwd __tmp_passwd;

void build_tmp_passwd(){
	__tmp_passwd.pw_name=myos_pass.name;
	__tmp_passwd.pw_passwd=myos_pass.password;
	__tmp_passwd.pw_uid=myos_pass.uid;
	__tmp_passwd.pw_gid=myos_pass.gid;
	__tmp_passwd.pw_gecos=myos_pass.gecos;
	__tmp_passwd.pw_dir=myos_pass.dir;
	__tmp_passwd.pw_shell=myos_pass.shell;
}


struct passwd* getpwent( void ) {

	passwd_myos* pass=myos_user_getID(_passwd_db_position);
	if (pass==NULL)
		return NULL;
	
	build_tmp_passwd();
	_passwd_db_position++;
	return &__tmp_passwd;
}
