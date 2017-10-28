#!/bin/python

#######################################################
# Author: Aleita Train 
# Class: OSU 372 Networking
# Description: Chat server using sockets API and a TCP
# connection. 
# Resourced# the python program in the text book 
# was my underlying resource for this program server.
#######################################################

from socket import *
import sys

def chatter(connection_socket, clientname, username):
	to_send = ""
	while 1: 
		# keep open until called to break 
		received = connection_socket.recv(501)[0:-1]
		if received == "":
			print "Connex to chat mate closed. Goodbye!"
			print "...waiting for a new connextion..."
			break
		print "{}>{}".format(clientname, received)
		to_send = ""
		while len(to_send) == 0 or len(to_send) > 500:
			to_send = raw_input("{}> ".format(username))
		
		if to_send == "\quit":
			print "Connex to chat mate closed. Goodbye!" 
			print "...waiting for a new connextion..." 
			break
		connection_socket.send(to_send)

def handshake(connection_socket, username):
	clientname = connection_socket.recv(1024)
	connection_socket.send(username)
	return clientname 

if __name__ == "__main__":
	if len(sys.argv)!=2:
		print "please specify port #"
		exit(1)
	
	serverport = sys.argv[1]
	serversocket = socket(AF_INET, SOCK_STREAM)
	serversocket.bind(('', int(serverport)))
	serversocket.listen(1)
	username = ""

	while len(username) == 0 or len(username) > 10:
		username = raw_input("Enter chat handle (10 characters or less): ")
		print "The server is ready to receive messages..."

	while 1: 
		connection_socket, address = serversocket.accept()
		print "Received connection on address {}".format(address)
		chatter(connection_socket, handshake(connection_socket, username), username) 
		connection_socket.close()


# open connection 
#from socket import *
#serverPort = 55666
#serverSocket = socket(AF_INET,SOCK_STREAM)
#serverSocket.bind(('',serverPort))
#serverSocket.listen(1)

#indicate ready response 
#print 'The server is ready to receive'
#while 1:
#  connectionSocket, addr = serverSocket.accept()
#  sentence = connectionSocket.recv(1024)
#  capitalizedSentence = sentence.upper()
#  connectionSocket.send(capitalizedSentence)
#  connectionSocket.close()

