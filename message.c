#include <stdio.h>
#include <string.h>
#include "message.h"
#include "err_proc.h"

const int BUFF_SIZE = 512;

void read_msg(struct message msg) {
    bzero(msg.buff, BUFF_SIZE);
    read_wrap(msg.socket, msg.buff, BUFF_SIZE);
    puts(msg.buff);
    if (strcmp(msg.buff, "E\0") == 0) {
        puts("Ñlient has disconnected.\n");
    }
}

void write_msg(struct message msg) {
    bzero(msg.buff, BUFF_SIZE);
    fgets(msg.buff, BUFF_SIZE, stdin);
    msg.buff[strlen(msg.buff) - 1] = '\0';
    write(msg.socket, msg.buff, strlen(msg.buff) * sizeof(char));
}