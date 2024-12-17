#pragma once
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>

int socket_wrap(int domain, int type, int protocol);
void bind_wrap(int sockfd, const struct sockaddr* addr, socklen_t addrlen);
int listen_wrap(int sockfd, int backlog);
int accept_wrap(int sockfd, struct sockaddr* addr, socklen_t *addrlen);
void connect_wrap(int sockfd, struct sockaddr* addr, socklen_t addrlen);
ssize_t read_wrap(int sockfd, char* buffer, int buflen);

char* find_p(char** arg_values, int arg_count);