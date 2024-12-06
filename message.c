#include <sys/types.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include "message.h"
#include "err_proc.h"
const int BUFF_SIZE = 512;
void read_msg(struct message msg) {
    bzero(msg.buff, BUFF_SIZE);
    msg.nread = Read(msg.socket, msg.buff, BUFF_SIZE);
    write(STDOUT_FILENO, msg.buff, msg.nread);
    if (strcmp(msg.buff, "E\n\0") == 0) {
        puts("�lient has disconnected.\n");
    }
}
void write_msg(struct message msg) {
    bzero(msg.buff, BUFF_SIZE);
    fgets(msg.buff, BUFF_SIZE, stdin);
    msg.buff[strlen(msg.buff) - 1] = '\n';
    msg.buff[strlen(msg.buff)] = '\0';
    write(msg.socket, msg.buff, strlen(msg.buff) * sizeof(char));
}