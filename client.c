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

	struct addrinfo serverAddress, *res;
	int state; // help us track ready status 

	memset((char *) &serverAddress, '\0',sizeof(serverAddress)); // clear address
	serverAddress.ai_family = AF_INET;
	serverAddress.ai_socktype = SOCK_STREAM;
	memcpy((char*)&serverAddress.ai_addr.s_addr, (char*(res->h_addr, res->h_length)));
	
	state = getaddrinfo(input_addr, port, &res);
	if(state != 0){
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
	if((sockfd = socket(res->ai_family, res->ai_socktype, res->ai_protocol)) == -1){
		fprintf(stderr, "Error in creating socket\n");
		exit(1);
	}
	return sockfd;
}


/***********************************************
 * CONNECT SOCKET FOR CHAT AWESOME
 * *********************************************/
void connect_socket(int sockfd, struct addrinfo * res) {
	int state; // for consisting update to state 
	if((status = connect(sockfd, res->ai_addr,res->ai_addlen)) == -1) {
		fprinft(stderr, "Error in connecting to the socket\n");
		exit(1);
	}
}
/************************************************
 * MAKE IT CHAT 
 * send initial message packet to 
 * host A server to establish connection 
 * PORTNUM
 * **********************************************/
void chat(int sockfd, char * chatHandle, char * serverAddress) {
	char input[500];
	char input[500];
	memset(input, 0, sizeof(input));
	memset(output, 0, sizeof(output));

	/* byte checking */
	int num_bytes_sent = 0;
	int state; // for maintaining ok state 

	while(1){
		while(strcmp(input, "\\quit\n" != 0)) {
			/* print chatHandle*/	
			printf("%s> ", chatHandle);
			fgets(input, 500, stdin);
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
				printf("%s> %s\n", serverAddress, output);
			}
			memset(input, 0, sizeof(input));
			memset(output, 0, sizeof(output));
		
		}exit(1);
	}
	close(sockfd);
	printf("Connection ended\n");
}

