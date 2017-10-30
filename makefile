.PHONY: client server

server:
	chmod +x server

client: 
	cc -o chatclient chatclient.c
	gcc chatclient.c
