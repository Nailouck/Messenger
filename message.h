#pragma once

struct message {
    int socket;
    char* buff;
};
void read_msg(struct message msg);
void write_msg(struct message msg);