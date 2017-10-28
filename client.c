/****************************************************
 * Chat Client 
 * Author: Aleita Train 
 * Class: CS 372, Oregon State University Fall 2017
 * Assignment: Project 1
 * References: Referenced OTP assignment four from my 
 * Operating Systems Class
 * **************************************************/

#include <sys/socket.h>
#include <sys/types.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_MSG_SIZE 500 
#define SERVER_PORT 6666

/*********************************************
 ***************** M A I N *******************
 ********************************************/
int main(int argc, char *argv[]){
	
	/* Prepare input buffer */	
	char buffer[500];
	memset(buffer, '\0', sizeof(buffer));

	/* Check for appropriate input*/
	if(argc!=3) {
		fprintf(stderr, "Usage: $ /chatclient <server address> <port>", argv[0]);
		exit(1);
	}

	/* Prepare and receive user chat handle username */
	char chatHandle[10];		
	getChatHandle(chatHandle);

	struct socketInfo * res = mySocketInfo(argv[1], argv[2]);
	int sockfd = create_socket(res);
	connect_socket(socfd, res);

	char serverAddress[10]
	handshake(sockfd, chatHandle, serverAddress);
	chat(sockfd, chatHandle, serverAddress);

	freeaddrinfo(res);

}

/************************************************
 * For handling username
 * *********************************************/
void getChatHandle(char * input) {
	printf("Please enter a 10 character chat handle: ");
	scanf("%s", input);
}


/***********************************************
 * PACKAGE SOCKET INFORMATION FOR CONEXX
 * *********************************************/
struct socketInfo * mySocketInfo(char * input_addr, char * port){

	struct addrinfo hints, *res

	memset((char *) &serverAddress, '\0',sizeof(serverAddres)); // clear address
	serverAddress.ai_family = AF_INET;
	serverAddress.ai_family = SOCK_STREAM;
	memcpy((char*)&serverAddress.ai_addr.s_addr, (char*(server->h_addr, server->h_length);

	if((status == getaddrinfo(input_addr, port, &hints, &res)) != 0) {
		printf(stderr, "getaddrinfo error: %s\nPlease check the servername or IP address\n",
		gai_sterror(status));
		exit(1);
	}
	return res;
}

/***********************************************
 * CREATE SOCKET FOR CHAT AWESOME 
 * *********************************************/
int create_socket(struct addrinfo * res) {
	int sockfd;
	if((sockfd = socket(res->ai_family, res->aid_scoktype, res->ai_protocol)) == -1){
		fprintf(stderr, "Error in creating socket\n");
		exit(1);
	}
	return sockfd;
}


/***********************************************
 * display users handle as prompt
 * *********************************************/




/************************************************
 * send initial message packet to 
 * host A server to establish connection 
 * PORTNUM
 * **********************************************/
