#include "err_proc.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>

int socket_wrap(int domain, int type, int protocol) {
    int res = socket(domain, type, protocol);
    if (res == -1) {
        perror("Opening socket error!");
        exit(EXIT_FAILURE);
    }
    return res;
}

void bind_wrap(int sockfd, const struct sockaddr* addr, socklen_t addrlen) {
    int res = bind(sockfd, addr, addrlen);
    if (res == -1) {
        perror("Binding error!");
        exit(EXIT_FAILURE);
    }
}

int listen_wrap(int sockfd, int backlog) {
    int res = listen(sockfd, backlog);
    if (res == -1) {
        perror("Listening error!");
        exit(EXIT_FAILURE);
    }
    return res;
}

int accept_wrap(int sockfd, struct sockaddr* addr, socklen_t *addrlen) {
    int res = accept(sockfd, addr, addrlen);
    if (res == -1) {
        perror("Accepting error!");
        exit(EXIT_FAILURE);
    }
    return res;
}

void connect_wrap(int sockfd, struct sockaddr* addr, socklen_t addrlen) {
    int res = connect(sockfd, addr, addrlen);
    if (res == -1) {
        perror("Connection error!");
        exit(EXIT_FAILURE);
    }
    puts("Connection is successful!\n");
}

ssize_t read_wrap(int sockfd, char* buffer, int buflen) {
    ssize_t res = read(sockfd, buffer, buflen);
    if (res == -1) {
        perror("Reading error!");
        exit(EXIT_FAILURE);
    }
    if (res == 0) { puts("Ñlient has disconnected.\n"); }
    return res;
}


char* find_p(char** arg_values, int arg_count) {
    for (int i = 0; i < arg_count; i++) {
        if (strcmp(arg_values[i], "-p") == 0 || strcmp(arg_values[i], "--port") == 0) {
            return arg_values[i + 1];
        }
    }
    return "Error\0";
}