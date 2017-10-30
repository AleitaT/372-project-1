# Aleita Train CS 372 Project 1

This is TCP chat client using the sockets api

## prep to execute server

Running the following command will prepare your python script to be executable with a certain command. Run the following make command: 

	make server 


## execute server
Now we can run the python server with the following command including a specified port number. 

	./server <port>

Where port is the number of the port you would like to communicate on.  

EXMPLE: 
	$ ./server 55667

## compile client 
Running the following command will prepare your c chat client program to executable with a certain command.  Run the following make command: 

	make client 

## execute start client 
Now we can run the command to execute the chat client program.  We need to include the hostname of the server program and port number to communicate one. Run the following command to start the client:

	./chatclient <hostname> <port number>

Where hostname should be hostname that server is running on. 
Where port number should be the same port number that server is running on. 
	
EXAMPLE:
	./chatclient flip3.engr.oregonstate.edu 4000

## to quit once running
	$  \quit

This will close connection, server will remain running and be avaialble for new connections until received a SIGINT to shut down. 
