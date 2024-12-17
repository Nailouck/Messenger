#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include "err_proc.h"
#include "message.h"

extern const int BUFF_SIZE;

typedef struct sockaddr sockaddr_t;

int main(int argc, char *argv[]) {

	if (strcmp(find_p(argv, argc), "Error\0") == 0) {
		argc += 2;
		argv[argc - 2] = "-p\0";
		argv[argc - 1] = "9898\0";
	}

	int client_socket = socket_wrap(AF_INET, SOCK_STREAM, 0);

	struct sockaddr_in addr;
	addr.sin_family = AF_INET;
	addr.sin_port = htons(atoi(find_p(argv, argc)));
	addr.sin_addr.s_addr = INADDR_ANY;

	connect_wrap(client_socket, (sockaddr_t*)&addr, sizeof(addr));
	
	char buff[BUFF_SIZE];
	struct message msg;
	msg.buff = buff;
	msg.socket = client_socket;

	do {
		write_msg(msg);
		if (strcmp(msg.buff, "E\0") == 0) { break; }
		read_msg(msg);
	}
	while (1);
	
	close(client_socket);
	return 0;
}