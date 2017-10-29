#!/bin/python

#######################################################
# Author: Aleita Train 
# Class: OSU 372 Networking
# Description: Chat server using sockets API and a TCP
# connection. 
# Resourceds:
# The python program in the text book was my underlying resource for this program server.
# http://www.bogotobogo.com/python/python_network_programming_tcp_server_client_chat_server_chat_client_select.php
#######################################################

from socket import *
import sys

def chatter(connection_socket, clientUserName, serverUserName):
	to_send = ""
	while 1: 
		# keep open until called to break 
		received = connection_socket.recv(501)[0:-1]
		if received != "":
			print "{}>{}".format(clientUserName, received)
		#to handle close signal (message will be empty)
		if received == "":
			print "..................................."	
			print "..................................."
			print "...Connection closed..............."
			print "...waiting for a new chat mate ...."
			print "..................................."	
			print "..................................."	
			break
		# prep message to send
		myMessage = ""
		# if message is outside the bounds, continue prompting
		# for proper input. 
		while len(myMessage) == 0 or len(myMessage) > 502:
			myMessage = raw_input("{}> ".format(serverUserName))	
		if myMessage == "\quit":
			print "..................................."	
			print "..................................."	
			print "Connection to chat mate closed. Goodbye!" 
			print "...waiting for a new connection..." 
			print "..................................."	
			print "..................................."	
			break
		# send a message 
		connection_socket.send(myMessage)

# handshake to exchange userNames
def handshake(connection_socket, serverUserame):
	clientUserName = connection_socket.recv(1024)
	connection_socket.send(serverUserName)
	return clientUserName
 
# main runner function
if __name__ == "__main__":
	# check for proper input
	if len(sys.argv)!=2:
		print "..................................."	
		print "..................................."	
		print "Please specify a port number."
		print "Consult the readme for more instruction"
		print "..................................."	
		print "..................................."	
		exit(1)
	# prep and create socket
	serverPort = sys.argv[1]
	serverSocket = socket(AF_INET, SOCK_STREAM)
	serverSocket.bind(('', int(serverPort)))
	serverSocket.listen(1)
	serverUserName = ""
	# we want the right size username, ask for until received
	while len(serverUserName) == 0 or len(serverUserName) > 10:
		serverUserName  = raw_input("Enter username (10 characters or less): ")
		# if we make it here, that means we have the right username
		print "..................................."	
		print "..............Welcome.............."	
		print "...........Ready to Chat .........."
		print "......waiting for connection......."	
		print "..................................."	
		# friendly messaging to make them feel comfortable chatting
	while 1: 
		# accept connection and alert chatter they are no longer alone
		connection_socket, connectionAddress = serverSocket.accept()
		print "Chat buddy joinin us on address {}".format(connectionAddress)
		print "Awaiting first message from client..."
		# dont forget to pass our username along to them. 
		chatter(connection_socket, handshake(connection_socket, serverUserName), serverUserName) 		# close connection
		connection_socket.close()

