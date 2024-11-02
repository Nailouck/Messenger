#include <stdlib.h>
#include <string.h>
#include <stdio.h>
 

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>

int main() {
        int server_socket;
        if (server_socket = socket(AF_INET, SOCK_STREAM, 0) < 0) {
                printf("Opening socket error!\n");
                return -1;
}
        struct sockaddr_in server_addres;
        server_addres.sin_family = AF_INET;
	server_addres.sin_addr.s_addr = INADDR_ANY;
        server_addres.sin_port = htons(9898);

        if (bind(server_socket, (struct sockaddr*) &server_addres, sizeof(server_addres)) < 0) {
                printf("Binding error!\n");
                return -2;
}

        close(server_socket);
        return 0;
}
