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
#include <netdb.h>

#define MAX_MSG_SIZE 500 
#define SERVER_PORT 6666

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
struct addrinfo * create_address_info(char * input_addr, char * port){

	struct addrinfo serverAddress, *server;
	int state; // help us track ready status 

	memset(&serverAddress, 0, sizeof serverAddress); // clear address
	serverAddress.ai_family = AF_INET;
	serverAddress.ai_socktype = SOCK_STREAM;
	
	state = getaddrinfo(input_addr, port, &serverAddress, &server);
	if(state != 0){
		fprintf(stderr, "getaddrinfo error: %s\nPlease check the servername or IP address\n",
		gai_strerror(state));
		exit(1);
	}
	return server;
}

/***********************************************
 * CREATE SOCKET FOR CHAT AWESOME 
 * *********************************************/
int create_socket(struct addrinfo * server) {
	int sockfd;
	sockfd = socket(server->ai_family, server->ai_socktype, server->ai_protocol);
	if(sockfd == -1) {
		fprintf(stderr, "Error in creating socket\n");
		exit(1);
	}
	return sockfd;
}


/***********************************************
 * CONNECT SOCKET FOR CHAT AWESOME
 * *********************************************/
void connect_socket(int sockfd, struct addrinfo * server) {
	int state; // for consisting update to state 
 	state = connect(sockfd, server->ai_addr,server->ai_addrlen);
	if(state == -1) {
		fprintf(stderr, "Error in connecting to the socket\n");
		exit(1);
	}
}

/************************************************
 * HAND SHAKE 
 *
 * **********************************************/
void handshake(int sockfd, char * chatHandle, char *serverAddress) {
	int sendIt = send(sockfd, chatHandle, strlen(chatHandle), 0);
	int recIt = recv(sockfd, serverAddress, 10, 0);
}

/************************************************
 * MAKE IT CHAT 
 * send initial message packet to 
 * host A server to establish connection 
 * PORTNUM
 * **********************************************/
void chat(int sockfd, char * chatHandle, char * serverAddress) {
	
	char input[500];
	char output[500];
	
	memset(input, 0, sizeof(input));
	memset(output, 0, sizeof(output));

	/* byte checking */
	int num_bytes_sent = 0;
	int state; // for maintaining ok state 
	
	fgets(input, 500, stdin);
	
	while(1){
		
		/* print chatHandle*/	
		printf("%s > ", chatHandle);
		
		fgets(input, 500, stdin);	
	
		if(strcmp(input, "\\quit\n") == 0) {
				break;
		}
			
		/* send a message */
		num_bytes_sent = send(sockfd, input, strlen(input), 0);
			
		/* check for byte errors */
		if(num_bytes_sent == -1) {
			fprintf(stderr, "ooop!  We've got a byte problem!\n");
			exit(1);
		}
		state = recv(sockfd, output, 500, 0);

		if(state == -1){
			fprintf(stderr, "Error: Host\n");
			exit(1);
		}
		else if(state == 0) {
			printf("Connection closed by server\n");
			break;
		}	
		else {
			printf("%s > %s\n", serverAddress, output);
		}
		memset(input, 0, sizeof(input));
		memset(output, 0, sizeof(output));
		
	}
	close(sockfd);
	printf("Connection ended\n");
}
/*********************************************
 ***************** M A I N *******************
 ********************************************/
int main(int argc, char *argv[]){
	/* Check for appropriate input*/
	if(argc != 3) {
		fprintf(stderr, "Usage: $ /chatclient <server address> <port>");
		exit(1);
	}
	
	/* Prepare and receive user chat handle username */
	char chatHandle[10];		
	getChatHandle(chatHandle);
	
	struct addrinfo * server = create_address_info(argv[1], argv[2]);
	int sockfd = create_socket(server);
	connect_socket(sockfd, server);

	char serverAddress[10];
	handshake(sockfd, chatHandle, serverAddress);
	chat(sockfd, chatHandle, serverAddress);

	freeaddrinfo(server);

}


