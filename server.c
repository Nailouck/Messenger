#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include "err_proc.h"

int main(int argc, char *argv[]) {

    if (argc < 2) {
        puts("Not enough program arguments! Example: ./object <port>\n");
        return -1;
    }

    int server_socket = Socket(AF_INET, SOCK_STREAM, 0);

    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(atoi(argv[1]));
    addr.sin_addr.s_addr = INADDR_ANY;

    Bind(server_socket, (struct sockaddr*) &addr, sizeof(addr));

    Listen(server_socket, 5);
    socklen_t adrlen = sizeof addr;
    int client_socket = Accept(server_socket, (struct sockaddr*) &addr, &adrlen);

    ssize_t nread;
    char buff[512];
    int disconnect = 0;
    do {
        if (disconnect == 3) { break; }
        bzero(buff, 512);
        nread = read(client_socket, buff, 512);
        if (nread == -1) {
            perror("Reading error!");
            exit(EXIT_FAILURE);
        }
        if (nread == 0) {
            printf("Ñlient has disconnected.\n");
            disconnect++;
        }

        write(STDOUT_FILENO, buff, nread);
        bzero(buff, 512);
        fgets(buff, 512, stdin);
        buff[strlen(buff) - 1] = '\n';
        buff[strlen(buff)] = '\0';
        write(client_socket, buff, strlen(buff) * sizeof(char));
    } while (buff[0] + buff[1] + buff[2] != 'E' + '\n' + '\0');
    

    sleep(1);
    close(client_socket);
    close(server_socket);
    return 0;
}
