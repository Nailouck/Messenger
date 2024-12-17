.PHONY: server client uninstall
all:

server: server.c err_proc.c message.c
	gcc -o server server.c err_proc.c message.c
client: client.c err_proc.c message.c
	gcc -o client client.c err_proc.c message.c
uninstall:
	rm server client
