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
	if(argc!=2) {
		fprintf(stderr, "Usage: please provide all necessary launch codes", argv[0]);
		exit(1);
	}

	/* Prepare and receive user chat handle/username */
	char chatHandle[10];		
	getChatHandle(chatHandle);

	

}

/************************************************
 * I live on host B
 * *********************************************/
int socket(int family, int type, int protocol){


/***********************************************
 * get the users handle by 
 * initial query
 * one word name up to 10 characters 
 * *********************************************/
void getChatHandle(char * userInput){
	fprintf("Ready to chat?  Enter a username (10 characters or less): ");
	scanf("%", userInput);
}
/***********************************************
 * display users handle as prompt
 * *********************************************/


/************************************************
 * send initial message packet to 
 * host A server to establish connection 
 * PORTNUM
 * **********************************************/
