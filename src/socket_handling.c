#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/ioctl.h>
#include <linux/if_ether.h>
#include <netinet/in.h>
//#include <arpa/inet.h>

//create a raw socket receiving raw data. Return the Socket's FD.
int create_socket(){
    
    int sock = 0;

    if ((sock = socket(AF_PACKET, SOCK_RAW, htons(ETH_P_IP))) < 0){
        perror("Problem while creating the socket...");
        exit(1);
    }

return sock;
}

//TODO: Create a list of all possible network interface to bind to, so the function get the interface she need.

//Take a socket's FD and and an interface as arguments and bind them.
void bind_socket_to_interface(char *interface, int socket){

    if (setsockopt(socket, SOL_SOCKET, SO_BINDTODEVICE, interface, strlen(interface) + 1) < 0) {
        perror("setsockopt bind device error.");
        close(socket);
        exit(1);
    }

}

 