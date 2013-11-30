

#ifndef _NETINET_IN_H_
#define _NETINET_IN_H_

#include <sys/types.h>
#include <sys/socket.h>

#define ntohs(n) \
    ((((uint16_t)(n) & 0xFF) << 8) | ((uint16_t)(n) >> 8))
#define ntohl(n) \
    (((uint32_t)(n) << 24) | (((uint32_t)(n) & 0xFF00) << 8) | (((uint32_t)(n) & 0x00FF0000) >> 8) | ((uint32_t)(n) >> 24))

#define htons ntohs
#define htonl ntohl

/* Standard well-defined IP protocols. */

enum {
    IPPROTO_IP = 0,        /* Dummy protocol for TCP.  */
#define IPPROTO_IP              IPPROTO_IP
    IPPROTO_HOPOPTS = 0,   /* IPv6 Hop-by-Hop options.  */
#define IPPROTO_HOPOPTS         IPPROTO_HOPOPTS
    IPPROTO_ICMP = 1,      /* Internet Control Message Protocol.  */
#define IPPROTO_ICMP            IPPROTO_ICMP
    IPPROTO_IGMP = 2,      /* Internet Group Management Protocol. */
#define IPPROTO_IGMP            IPPROTO_IGMP
    IPPROTO_IPIP = 4,      /* IPIP tunnels (older KA9Q tunnels use 94).  */
#define IPPROTO_IPIP            IPPROTO_IPIP
    IPPROTO_TCP = 6,       /* Transmission Control Protocol.  */
#define IPPROTO_TCP             IPPROTO_TCP
    IPPROTO_EGP = 8,       /* Exterior Gateway Protocol.  */
#define IPPROTO_EGP             IPPROTO_EGP
    IPPROTO_PUP = 12,      /* PUP protocol.  */
#define IPPROTO_PUP             IPPROTO_PUP
    IPPROTO_UDP = 17,      /* User Datagram Protocol.  */
#define IPPROTO_UDP             IPPROTO_UDP
    IPPROTO_IDP = 22,      /* XNS IDP protocol.  */
#define IPPROTO_IDP             IPPROTO_IDP
    IPPROTO_TP = 29,       /* SO Transport Protocol Class 4.  */
#define IPPROTO_TP              IPPROTO_TP
    IPPROTO_DCCP = 33,     /* Datagram Congestion Control Protocol.  */
#define IPPROTO_DCCP            IPPROTO_DCCP
    IPPROTO_IPV6 = 41,     /* IPv6 header.  */
#define IPPROTO_IPV6            IPPROTO_IPV6
    IPPROTO_ROUTING = 43,  /* IPv6 routing header.  */
#define IPPROTO_ROUTING         IPPROTO_ROUTING
    IPPROTO_FRAGMENT = 44, /* IPv6 fragmentation header.  */
#define IPPROTO_FRAGMENT        IPPROTO_FRAGMENT
    IPPROTO_RSVP = 46,     /* Reservation Protocol.  */
#define IPPROTO_RSVP            IPPROTO_RSVP
    IPPROTO_GRE = 47,      /* General Routing Encapsulation.  */
#define IPPROTO_GRE             IPPROTO_GRE
    IPPROTO_ESP = 50,      /* encapsulating security payload.  */
#define IPPROTO_ESP             IPPROTO_ESP
    IPPROTO_AH = 51,       /* authentication header.  */
#define IPPROTO_AH              IPPROTO_AH
    IPPROTO_ICMPV6 = 58,   /* ICMPv6.  */
#define IPPROTO_ICMPV6          IPPROTO_ICMPV6
    IPPROTO_NONE = 59,     /* IPv6 no next header.  */
#define IPPROTO_NONE            IPPROTO_NONE
    IPPROTO_DSTOPTS = 60,  /* IPv6 destination options.  */
#define IPPROTO_DSTOPTS         IPPROTO_DSTOPTS
    IPPROTO_MTP = 92,      /* Multicast Transport Protocol.  */
#define IPPROTO_MTP             IPPROTO_MTP
    IPPROTO_ENCAP = 98,    /* Encapsulation Header.  */
#define IPPROTO_ENCAP           IPPROTO_ENCAP
    IPPROTO_PIM = 103,     /* Protocol Independent Multicast.  */
#define IPPROTO_PIM             IPPROTO_PIM
    IPPROTO_COMP = 108,    /* Compression Header Protocol.  */
#define IPPROTO_COMP            IPPROTO_COMP
    IPPROTO_SCTP = 132,    /* Stream Control Transmission Protocol.  */
#define IPPROTO_SCTP            IPPROTO_SCTP
    IPPROTO_UDPLITE = 136, /* UDP-Lite protocol.  */
#define IPPROTO_UDPLITE         IPPROTO_UDPLITE
    IPPROTO_RAW = 255,     /* Raw IP packets.  */
#define IPPROTO_RAW             IPPROTO_RAW
    IPPROTO_MAX
};

typedef uint16_t in_port_t;
typedef uint32_t in_addr_t;

struct in_addr {
    in_addr_t s_addr;
};

struct sockaddr_in {
    sa_family_t sin_family;
    in_port_t sin_port;      /* Port number.  */
    struct in_addr sin_addr; /* Internet address.  */

    /* Pad to size of `struct sockaddr'. */
    unsigned char sin_zero[
        sizeof( struct sockaddr ) -
        sizeof( sa_family_t ) -
        sizeof( in_port_t ) -
        sizeof( struct in_addr )
    ];
};

#endif /* _NETINET_IN_H_ */
