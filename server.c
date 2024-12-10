#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include "err_proc.h"
#include "message.h"

extern const int BUFF_SIZE;

int main(int argc, char *argv[]) {

    if (argc < 2) {
        puts("Not enough program arguments! Example: ./server.o <port>\n");
        return -1;
    }

    int server_socket = Socket(AF_INET, SOCK_STREAM, 0);

    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(atoi(argv[1]));
    addr.sin_addr.s_addr = INADDR_ANY;

    Bind(server_socket, (struct sockaddr*) &addr, sizeof(addr));
    Listen(server_socket, 1);

    socklen_t adrlen = sizeof addr;
    int client_socket = Accept(server_socket, (struct sockaddr*) &addr, &adrlen);

    char buff[BUFF_SIZE];
    struct message msg;
    msg.buff = buff;
    msg.socket = client_socket;

    do {
        read_msg(msg);
        write_msg(msg);
    } while (strcmp(msg.buff, "E\0") != 0);
    

    close(client_socket);
    close(server_socket);
    return 0;
}
