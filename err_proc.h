#pragma once
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>

int Socket(int domain, int type, int protocol);
void Bind(int sockfd, const struct sockaddr* addr, socklen_t addrlen);
int Listen(int sockfd, int backlog);
int Accept(int sockfd, struct sockaddr* addr, socklen_t *addrlen);
void Connect(int sockfd, struct sockaddr* addr, socklen_t addrlen);
ssize_t Read(int sockfd, char* buffer, int buflen);