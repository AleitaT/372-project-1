# Aleita Train CS 372 Project 1

This is FTP chat client using the sockets api

## start server
	make server port="<PORT#>"

Where <PORT#> is replaced with a port number. 
Suggested port range between 40000 - 60000

## compile client 
	make client 

## execute start client 
	./chatclient <hostname> <port number>

Where hostname should be hostname that server is running on. 
Where port number should be the same port number that server is running on. 

## to quit once running
	>  \quit

This will close connection, server will remain running and be avaialble for new connections until received a SIGINT to shut down. 
