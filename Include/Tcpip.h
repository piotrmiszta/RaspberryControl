//
// Created by programowanie on 30.01.23.
//

#ifndef RASPBERRYCONTROL_TCPIP_H
#define RASPBERRYCONTROL_TCPIP_H
#include <sys/socket.h>
#include <netinet/in.h>
typedef struct Tcpip {
    int sockFd;
    int connFd;
    struct sockaddr_in servaddr;
}Tcpip;

void tcp_init();



#endif //RASPBERRYCONTROL_TCPIP_H
