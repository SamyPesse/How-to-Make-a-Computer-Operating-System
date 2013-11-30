
 

#include <stdlib.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>

char* inet_ntoa( struct in_addr in ) {
    unsigned int ip;
    static char __inet_ntoa_result[18];
    int i;
    uint8_t bytes[4];
    uint8_t* addrbyte;

    ip = in.s_addr;

    addrbyte = (uint8_t *)&ip;

    for(i = 0; i < 4; i++) {
        bytes[i] = *addrbyte++;
    }

    snprintf (__inet_ntoa_result, 18, "%d.%d.%d.%d", bytes[0], bytes[1], bytes[2], bytes[3]);

    return __inet_ntoa_result;
}
