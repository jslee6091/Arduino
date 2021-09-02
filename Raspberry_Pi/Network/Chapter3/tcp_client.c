#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <unistd.h>

int main(int argc, char *argv[]){
    int fd_socket;
    struct sockaddr_in addr;
    struct hostent *host;
    char message[100];
    char buf[100];
    char buffer[BUFSIZ];
    
    // Socket system call
    if((fd_socket = socket(AF_INET, SOCK_STREAM, 0)) == -1){
	perror("client : socket");
	return 1;
    }
    
    // Get hostname by DNS
    host = gethostbyname(argv[1]);
    if(host == NULL){
        printf("Host not found! : %s\n\r", argv[1]);
        return 1;
    }

    bzero((char *)&addr, sizeof(addr));
    addr.sin_family = AF_INET;
    memcpy((char *)&addr.sin_addr, host->h_addr, host->h_length);
    addr.sin_port = htons(atoi(argv[2]));

    inet_ntop(AF_INET, &addr.sin_addr, buf, sizeof(buf));
    printf("Trying %s .. \n", buf);
    
    // Access server socket
    if(connect(fd_socket, (struct sockaddr *)&addr, sizeof(addr))== -1){
    	perror("client: connect");
        return 1;
    }

    printf("Connected %s.\n", argv[1]);
    printf("send message : ");
    fgets(message, sizeof(message), stdin);
    
    // Send message to server
    if(write(fd_socket, message, strlen(message) + 1) == -1){
    	perror("client: write");
	return 1;
    }

    // Receive message from server
    if(read(fd_socket, buffer, BUFSIZ) == -1){
    	perror("client: read");
	return 1;
    }

    printf("message from server : %s\n", buffer);
    close(fd_socket);
    return 0;
}
