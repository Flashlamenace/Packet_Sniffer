#include "../includes/protocol_stack.h"
#include "../includes/socket_handling.h"
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>

int main (void){
    char *opt = "wlp1s0";
    int socket_fd = create_socket();
    bind_socket_to_interface(opt, socket_fd);

    int buffer_lenght;
    unsigned char *buffer = (unsigned char*) malloc(65536);
    memset(buffer,0,65536);
   
    while (1) {
    
        struct sockaddr saddr;
        int saddr_len = sizeof (saddr);

        buffer_lenght = recvfrom(socket_fd, buffer, 65536, 0, &saddr, (socklen_t *) &saddr_len);
        
        header_handling(buffer, buffer_lenght);

    }

    free(buffer);
}
   