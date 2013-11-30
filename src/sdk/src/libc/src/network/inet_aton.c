
 

#include <stdlib.h>
#include <netinet/in.h>
#include <arpa/inet.h>

int inet_aton( const char* cp, struct in_addr* inp ) {
    int i;
    unsigned int ip = 0;
    char* tmp= ( char* )cp;

    for ( i = 24; ; ) {
        long j;

        j = strtoul( tmp, &tmp, 0 );

        if ( *tmp == 0 ) {
            ip |= j;

            break;
        } else if ( *tmp == '.' ) {
            if ( j > 255 ) {
                return 0;
            }

            ip |= ( j << i );

            if ( i > 0 ) {
                i -= 8;
            }

            ++tmp;

            continue;
        }

        return 0;
    }

    inp->s_addr = htonl( ip );

    return 1;
}
