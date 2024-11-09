#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include "err_proc.h"

int main() {

    int server_socket = Socket(AF_INET, SOCK_STREAM, 0);

    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(9898);
    addr.sin_addr.s_addr = INADDR_ANY;

    Bind(server_socket, (struct sockaddr*) &addr, sizeof(addr));

    Listen(server_socket, 5);
    socklen_t adrlen = sizeof addr;
    int client_socket = Accept(server_socket, (struct sockaddr*) &addr, &adrlen);

    ssize_t nread;
    char buff[256];
    nread = read(client_socket, buff, 256);
    if (nread == -1) {
        perror("Reading error!");
        exit(EXIT_FAILURE);
    }
    if (nread == 0) {
        printf("End of file.\n");
    }

    write(STDOUT_FILENO, buff, nread);
    write(client_socket, buff, nread);

    sleep(1);
    close(client_socket);
    close(server_socket);
    return 0;
}
