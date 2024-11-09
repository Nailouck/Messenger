#include <stdlib.h>
#include <stdio.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include "err_proc.h"

int main(int argc, char* argv[]) {
	int client_socket = Socket(AF_INET, SOCK_STREAM, 0);
	struct sockaddr_in addr;
	addr.sin_family = AF_INET;
	addr.sin_port = htons(9898);
	addr.sin_addr.s_addr = INADDR_ANY;

	Connect(client_socket, (struct sockaddr*)&addr, sizeof(addr));

	write(client_socket, "Hello\n", 6);
	char buff[256];
	ssize_t nread = read(client_socket, buff, 256);
	if (nread == -1) {
		perror("Reading error!");
		exit(EXIT_FAILURE);
	}
	if (nread == 0) {
		printf("End of file.\n");
	}
	write(STDOUT_FILENO, buff, nread);
	close(client_socket);
	return 0;
}