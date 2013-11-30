

#ifndef _ARPA_INET_H_
#define _ARPA_INET_H_

#include <netinet/in.h> /* struct in_addr */

int inet_aton( const char* cp, struct in_addr* inp );

in_addr_t inet_addr( const char* cp );

in_addr_t inet_network( const char* cp );

char* inet_ntoa( struct in_addr in );

struct in_addr inet_makeaddr( int net, int host );

in_addr_t inet_lnaof( struct in_addr in );

in_addr_t inet_netof( struct in_addr in );

#endif /* _ARPA_INET_H_ */
