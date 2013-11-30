

#ifndef _SYS_SOCKET_H_
#define _SYS_SOCKET_H_

/* Protocol families.  */

#define PF_UNSPEC       0       /* Unspecified.  */
#define PF_LOCAL        1       /* Local to host (pipes and file-domain).  */
#define PF_UNIX         PF_LOCAL /* POSIX name for PF_LOCAL.  */
#define PF_FILE         PF_LOCAL /* Another non-standard name for PF_LOCAL.  */
#define PF_INET         2       /* IP protocol family.  */
#define PF_AX25         3       /* Amateur Radio AX.25.  */
#define PF_IPX          4       /* Novell Internet Protocol.  */
#define PF_APPLETALK    5       /* Appletalk DDP.  */
#define PF_NETROM       6       /* Amateur radio NetROM.  */
#define PF_BRIDGE       7       /* Multiprotocol bridge.  */
#define PF_ATMPVC       8       /* ATM PVCs.  */
#define PF_X25          9       /* Reserved for X.25 project.  */
#define PF_INET6        10      /* IP version 6.  */
#define PF_ROSE         11      /* Amateur Radio X.25 PLP.  */
#define PF_DECnet       12      /* Reserved for DECnet project.  */
#define PF_NETBEUI      13      /* Reserved for 802.2LLC project.  */
#define PF_SECURITY     14      /* Security callback pseudo AF.  */
#define PF_KEY          15      /* PF_KEY key management API.  */
#define PF_NETLINK      16
#define PF_ROUTE        PF_NETLINK /* Alias to emulate 4.4BSD.  */
#define PF_PACKET       17      /* Packet family.  */
#define PF_ASH          18      /* Ash.  */
#define PF_ECONET       19      /* Acorn Econet.  */
#define PF_ATMSVC       20      /* ATM SVCs.  */
#define PF_SNA          22      /* Linux SNA Project */
#define PF_IRDA         23      /* IRDA sockets.  */
#define PF_PPPOX        24      /* PPPoX sockets.  */
#define PF_WANPIPE      25      /* Wanpipe API sockets.  */
#define PF_BLUETOOTH    31      /* Bluetooth sockets.  */
#define PF_IUCV         32      /* IUCV sockets.  */
#define PF_RXRPC        33      /* RxRPC sockets.  */
#define PF_ISDN         34      /* mISDN sockets.  */
#define PF_MAX          35      /* For now..  */

/* Address families. */

#define AF_UNSPEC    PF_UNSPEC
#define AF_LOCAL     PF_LOCAL
#define AF_UNIX      PF_UNIX
#define AF_FILE      PF_FILE
#define AF_INET      PF_INET
#define AF_AX25      PF_AX25
#define AF_IPX       PF_IPX
#define AF_APPLETALK PF_APPLETALK
#define AF_NETROM    PF_NETROM
#define AF_BRIDGE    PF_BRIDGE
#define AF_ATMPVC    PF_ATMPVC
#define AF_X25       PF_X25
#define AF_INET6     PF_INET6
#define AF_ROSE      PF_ROSE
#define AF_DECnet    PF_DECnet
#define AF_NETBEUI   PF_NETBEUI
#define AF_SECURITY  PF_SECURITY
#define AF_KEY       PF_KEY
#define AF_NETLINK   PF_NETLINK
#define AF_ROUTE     PF_ROUTE
#define AF_PACKET    PF_PACKET
#define AF_ASH       PF_ASH
#define AF_ECONET    PF_ECONET
#define AF_ATMSVC    PF_ATMSVC
#define AF_SNA       PF_SNA
#define AF_IRDA      PF_IRDA
#define AF_PPPOX     PF_PPPOX
#define AF_WANPIPE   PF_WANPIPE
#define AF_BLUETOOTH PF_BLUETOOTH
#define AF_IUCV      PF_IUCV
#define AF_RXRPC     PF_RXRPC
#define AF_ISDN      PF_ISDN
#define AF_MAX       PF_MAX

/* Types of sockets. */

enum socket_type {
  SOCK_STREAM = 1,              /* Sequenced, reliable, connection-based
                                   byte streams.  */
#define SOCK_STREAM SOCK_STREAM
  SOCK_DGRAM = 2,               /* Connectionless, unreliable datagrams
                                   of fixed maximum length.  */
#define SOCK_DGRAM SOCK_DGRAM
  SOCK_RAW = 3,                 /* Raw protocol interface.  */
#define SOCK_RAW SOCK_RAW
};

typedef unsigned short int sa_family_t;
typedef unsigned int socklen_t;

struct sockaddr {
    sa_family_t sa_family;
    char sa_data[ 14 ];
};

int socket( int domain, int type, int protocol );
int connect( int fd, const struct sockaddr* address, socklen_t addrlen );

/* Not implemented functions
int socketpair( int d, int type, int protocol, int sv[2] );

int bind( int sockfd, const struct sockaddr *addr,
          socklen_t addrlen );

int getsockname( int s, struct sockaddr *name, socklen_t *namelen );

int getpeername( int s, struct sockaddr *name, socklen_t *namelen );

ssize_t send( int s, const void *buf, size_t len, int flags );

ssize_t sendto( int s, const void *buf, size_t len, int flags,
                const struct sockaddr *to, socklen_t tolen );

ssize_t sendmsg( int s, const struct msghdr *msg, int flags );

ssize_t recv( int s, void *buf, size_t len, int flags );

ssize_t recvfrom( int s, void *buf, size_t len, int flags,
                  struct sockaddr *from, socklen_t *fromlen );

ssize_t recvmsg( int s, struct msghdr *msg, int flags );

int getsockopt( int s, int level, int optname,
                void *optval, socklen_t *optlen );

int setsockopt( int s, int level, int optname,
                const void *optval, socklen_t optlen );

int listen( int sockfd, int backlog );

int accept( int sockfd, struct sockaddr *addr, socklen_t *addrlen );

int shutdown( int s, int how );
*/

#endif /* _SYS_SOCKET_H_ */
