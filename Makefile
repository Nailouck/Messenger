.PHONY: server.o client.o uninstall
all:

server.o: server.c err_proc.c
	gcc -o server.o server.c err_proc.c message.c
client.o: client.c
	gcc -o client.o client.c err_proc.c message.c
uninstall:
	rm server.o
	rm client.o
