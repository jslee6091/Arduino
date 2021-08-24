#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#define BUFSIZE 1024

int main(int argc, char *argv[]){
    int sockfd;
    struct sockaddr_in servAddr;
    struct sockaddr_in clntAddr;
    char recvBuffer[BUFSIZE + 1];
    int recvLen, clntLen;

    // Make UDP Socket
    if((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) == -1){
        perror("socket failed");
        return 1;
    }
    
    // Initialize servAddr to 0
    memset(&servAddr, 0, sizeof(servAddr));
    
    // Store IP and Port to servAddr
    servAddr.sin_family = AF_INET;
    servAddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servAddr.sin_port = htons(atoi(argv[1]));

    // Connect address information to socket
    if(bind(sockfd, (struct sockaddr*)&servAddr, sizeof(servAddr)) == -1){
        perror("bind failed");
        return 1;
    }

    while(1){
	    clntLen = sizeof(clntAddr);
        
        // Receive data from sockfd, store in recvBuffer, and store client address in clntAddr
	    if((recvLen=recvfrom(sockfd, recvBuffer, BUFSIZE, 0, (struct sockaddr*)&clntAddr, &clntLen)) == -1){
		    perror("recvfrom failed");
		    return 1;
	    }
	    recvBuffer[recvLen] = '\0';
        // Print received data
	    printf("Received : %s\n", recvBuffer);

        // Send received data to client
        if(sendto(sockfd, recvBuffer, recvLen, 0, (struct sockaddr*)&clntAddr, sizeof(clntAddr)) != recvLen){
            perror("sendto failed");
            return 1;
        }
    }

    close(sockfd);
    return 0;
}
