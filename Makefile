.PHONY: server.o client.o uninstall run
all:

server.o: server.c err_proc.c
	gcc -o server.o server.c err_proc.c
client.o: client.c
	gcc -o client.o client.c err_proc.c
uninstall:
	rm server.o
	rm client.o
runserv:
	./server.o
runcli:
	./client.o
