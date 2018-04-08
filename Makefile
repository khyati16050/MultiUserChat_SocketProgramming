all:
	gcc -o serv server_ass2.c -lpthread
	gcc -o cli client_ass2.c -lpthread
clean:
	rm serv
	rm cli
