
 

#include <pwd.h>

extern int _passwd_db_position;

void endpwent( void ) {
    _passwd_db_position = 0;
}
