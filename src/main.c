#include "../includes/protocol_stack.h"
#include "../includes/socket_handling.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <signal.h>

volatile sig_atomic_t stop;
void handle_sigint(int sig) {
    stop = 1;
}

int main (void){
    char *opt = "wlp1s0";
    int socket_fd = create_socket();
    bind_socket_to_interface(opt, socket_fd);

    int buffer_lenght;
    unsigned char *buffer = (unsigned char*) malloc(65536);
    memset(buffer,0,65536);
   
    signal(SIGINT, handle_sigint);

    while (!stop) {
    
        struct sockaddr saddr;
        int saddr_len = sizeof (saddr);

        buffer_lenght = recvfrom(socket_fd, buffer, 65536, 0, &saddr, (socklen_t *) &saddr_len);
        if (buffer_lenght < 0) {
            perror("recvfrom failed");
            break;
        }
        
        print_all_sock_hdr(buffer, buffer_lenght);
    }

    free(buffer);
}
   