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
		puts("Not enough program arguments! Example: ./client.o <port>\n");
		return -1;
	}

	int client_socket = Socket(AF_INET, SOCK_STREAM, 0);

	struct sockaddr_in addr;
	addr.sin_family = AF_INET;
	addr.sin_port = htons(atoi(argv[1]));
	addr.sin_addr.s_addr = INADDR_ANY;

	Connect(client_socket, (struct sockaddr*)&addr, sizeof(addr));
	
	char buff[BUFF_SIZE];
	struct message msg;
	msg.buff = buff;
	msg.socket = client_socket;

	do {
		write_msg(msg);
		if (strcmp(msg.buff, "E\n\0") == 0) { break; }
		read_msg(msg);
	}
	while (1);
	
	close(client_socket);
	return 0;
}