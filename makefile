.PHONY: client server

server:
	python server.py ${port}

client: 
	cc -o chatclient chatclient.c
	gcc chatclient.c
