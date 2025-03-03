void payload_print(unsigned char *buffer, int buffer_lenght);
void tcp_header(unsigned char *buffer);
void ip_header(unsigned char *buffer);
void ethernet_header(unsigned char *buffer);

void print_all_sock_hdr(unsigned char *buffer, int buffer_lenght);