#######################################################
# Author: Aleita Train 
# Class: OSU 372 Networking
# Description: Chat server using sockets API and a TCP
# connection. 
# Resourced# the python program in the text book 
# was my underlying resource for this program server.
#######################################################


# open connection 
from socket import *
serverPort = 55666
serverSocket = socket(AF_INET,SOCK_STREAM)
serverSocket.bind(('',serverPort))
serverSocket.listen(1)

#indicate ready response 
print 'The server is ready to receive'
while 1:
  connectionSocket, addr = serverSocket.accept()
  sentence = connectionSocket.recv(1024)
  capitalizedSentence = sentence.upper()
  connectionSocket.send(capitalizedSentence)
  connectionSocket.close()

