int create_socket();
void bind_socket_to_interface(char *interface, int sock);
unsigned char *raw_data(int socket);