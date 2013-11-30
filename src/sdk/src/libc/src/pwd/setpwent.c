
 

#include <pwd.h>

extern int _passwd_db_position;

void setpwent( void ) {
    _passwd_db_position = 0;
}
