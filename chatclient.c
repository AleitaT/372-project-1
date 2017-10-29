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

void chat(int sockfd, char * clientUserName, char * serverAddress);
void getChatHandle(char * input);
struct addrinfo * packageConnection(char * addressInput, char * porto);
int establish(struct addrinfo * server);
void connection(int sockfd, struct addrinfo * server);
void handshake(int sockfd, char * clientUserName, char *serverAddress);		
void clear_input();
	
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
	char clientUserName[10];		
	getChatHandle(clientUserName);
	
	struct addrinfo * server = packageConnection(argv[1], argv[2]);
	int sockfd = establish(server);
	connection(sockfd, server);

	char serverAddress[10];
	handshake(sockfd, clientUserName, serverAddress);
	chat(sockfd, clientUserName, serverAddress);

	freeaddrinfo(server); // from man pages
}

/************************************************
 * For handling username
 * accept a pointer to buffer for character input 
 * Clears input if needs to take new name 
* *********************************************/
void getChatHandle(char * input) {
		printf("Please enter a 10 character chat handle: ");
		scanf("%s", input);
		// strings to long, try again. 
	 	if((strlen(input) > 10)) {
			clear_input(); // clear input so we don't end up with first name
			getChatHandle(input);
		}
}
/***************************************************
 * Just a little helper function for clearing
 * referenced: https://stackoverflow.com/questions/31633005/validate-the-type-of-input-in-a-do-while-loop-c
 * ***********************************************/
void clear_input() {
	char c;
	while((c = getchar()) != '\n' && c != EOF);
}

/***********************************************
 * PACKAGE SOCKET INFORMATION FOR CONEXX
 * Referenced man pages also: 
 * http://man7.org/linux/man-pages/man3/getaddrinfo.3.html
 * http://pubs.opengroup.org/onlinepubs/009695399/functions/gai_strerror.html
 * *********************************************/
struct addrinfo * packageConnection(char * addressInput, char * porto){

	struct addrinfo serverAddress, *server;
	int state; // help us track ready status 

	memset(&serverAddress, 0, sizeof serverAddress); // clear address
	serverAddress.ai_family = AF_INET; // referneced 344 assignment 4 
	serverAddress.ai_socktype = SOCK_STREAM; // and the book of course
	
	state = getaddrinfo(addressInput, porto, &serverAddress, &server);	
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
int establish(struct addrinfo * server) {
	/* for storing socket creation state */
	int sockfd;
	sockfd = socket(server->ai_family, server->ai_socktype, server->ai_protocol);
	/* Check to see if an error occured */
	if(sockfd == -1) {
		fprintf(stderr, "Error in creating socket\n");
		exit(1);
	}
	return sockfd;
}

/***********************************************
 * CONNECT SOCKET FOR CHAT AWESOME
 * *********************************************/
void connection(int sockfd, struct addrinfo * server) {
	int state; 
	/* for tracking socket connection state */  
 	state = connect(sockfd, server->ai_addr,server->ai_addrlen);
	if(state == -1) {
		fprintf(stderr, "Error in connecting to the socket\n");
		exit(1);
	}
}

/************************************************
 * HAND SHAKE 
 * **********************************************/
void handshake(int sockfd, char * clientUserName, char *serverAddress) {
	int sendIt = send(sockfd, clientUserName, strlen(clientUserName), 0);
	int recIt = recv(sockfd, serverAddress, 10, 0);
}

/************************************************
 * MAKE IT CHAT 
 * send initial message packet to 
 * host A server to establish connection 
 * PORTNUM
 * **********************************************/
void chat(int sockfd, char * clientUserName, char * serverAddress) {
	
	char input[503]; // check to see trailing characters, may need to adjust
	char output[501]; // tested and adjusted 
	
	memset(input, 0, sizeof(input));
	memset(output, 0, sizeof(output));

	/* byte checking */
	int bytesSent = 0;
	int state; // for maintaining ok state 
	
	fgets(input, 500, stdin);
	
	while(1){	
		/* print client user name before message input*/	
		printf("%s > ", clientUserName);
		fgets(input, 502, stdin);	

		if(strcmp(input, "\\quit\n") == 0) {
				exit(1);
		}

		/* send a message	and check for byte errors */
		bytesSent = send(sockfd, input, strlen(input), 0);	
		if(bytesSent == -1) {
			fprintf(stderr, "ooop!  We've got a byte problem!\n");
			exit(1);
		}

		state = recv(sockfd, output, 500, 0);
		switch(state){
			case -1 :
				fprintf(stderr, "Error: bad receive.\n");
				exit(1);		
			case 0 :
				printf("Connection closed by server\n");
				exit(1);			
			default: 
				printf("%s > %s\n", serverAddress, output);
		}

		memset(input, 0, sizeof(input));
		memset(output, 0, sizeof(output));
	}
	close(sockfd);
	printf("Connection ended\n");
}

