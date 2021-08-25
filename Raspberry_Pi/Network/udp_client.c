#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#define BUFSIZE 1024

/*
  int sendto(
  	int s,		// socket descriptor number
	char *buf,	// Sending data buffer
	int length,	// size of buffer
	int flags,	// usually 0
	sockaddr *to,	// socket address struct of receiver
	int tolen	// size of to address
  )

  int recvfrom(
  	int s		// socket descriptor number
	char *buf,	// Sending data buffer
	int length,	// size of buffer
	int flags,	// usually 0
	sockaddr *from,	// socket address struct of sender
	int &tolen	// pointer of from address
  )
*/

int main(int argc, char *argv[]){
    int sockfd;
    struct sockaddr_in servAddr;
    char sendBuffer[BUFSIZE + 1], recvBuffer[BUFSIZE + 1];
    int recvLen, servLen;

    if(argc != 3){
	    printf("Usage: %s IP_address Port\n", argv[0]);
	    return 1;
    }
    
    // Make UDP Socket
    if((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) == -1){
	perror("socket failed");
	return 1;
    }
    memset(&servAddr, 0, sizeof(servAddr));
    
    // Store IP and Port to servAddr
    servAddr.sin_family = AF_INET;
    // inet_addr converts decimal address to binary IP(only IPv4)
    servAddr.sin_addr.s_addr = inet_addr(argv[1]);
    servAddr.sin_port = htons(atoi(argv[2]));

    while(1){
	    printf("Input sending message ==> ");
   	    fgets(sendBuffer, BUFSIZE, stdin);
	    if(!strncmp(sendBuffer, "quit", 4)){
		    break;
	    }

	    // Send address of server every time when send message to server
	    if(sendto(sockfd, sendBuffer,strlen(sendBuffer), 0, (struct sockaddr*)&servAddr, sizeof(servAddr)) != strlen(sendBuffer)){
		    perror("sendto failed");
		    return 1;
	    }
	    servLen = sizeof(servAddr);

	    if((recvLen=recvfrom(sockfd, recvBuffer,strlen(recvBuffer), 0, (struct sockaddr*)&servAddr, &servLen)) == -1){
		    perror("recvfrom failed");
		    return 1;
	    }
	    recvBuffer[recvLen] = '\0';
	    printf("Received : %s\n", recvBuffer);
    }

    close(sockfd);
    return 0;
}
