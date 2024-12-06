#pragma once
struct message {
    int socket;
    ssize_t nread;
    char* buff;
};
void read_msg(struct message msg);
void write_msg(struct message msg);