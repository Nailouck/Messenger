#include "err_proc.h"
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>

int Socket(int domain, int type, int protocol) {
    int res = socket(domain, type, protocol);
    if (res == -1) {
        perror("Opening socket error!");
        exit(EXIT_FAILURE);
    }
    return res;
}
void Bind(int sockfd, const struct sockaddr* addr, socklen_t addrlen) {
    int res = bind(sockfd, addr, addrlen);
    if (res == -1) {
        perror("Binding error!");
        exit(EXIT_FAILURE);
    }
}
int Listen(int sockfd, int backlog) {
    int res = listen(sockfd, backlog);
    if (res == -1) {
        perror("Listening error!");
        exit(EXIT_FAILURE);
    }
    return res;
}
int Accept(int sockfd, struct sockaddr* addr, socklen_t *addrlen) {
    int res = accept(sockfd, addr, addrlen);
    if (res == -1) {
        perror("Accepting error!");
        exit(EXIT_FAILURE);
    }
    return res;
}
void Connect(int sockfd, struct sockaddr* addr, socklen_t addrlen) {
    int res = connect(sockfd, addr, addrlen);
    if (res == -1) {
        perror("Connection error!");
        exit(EXIT_FAILURE);
    }
}