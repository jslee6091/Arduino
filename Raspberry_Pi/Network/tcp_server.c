#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <unistd.h>
#include <stdlib.h>

int main(int argc, char *argv[]){
    int fd_socket, fd_accept;
    int clilen;
    struct sockaddr_in addr, cli_addr;
    char buf[100];
    char buffer[BUFSIZ];
    
    // Socket system call
    if((fd_socket = socket(AF_INET, SOCK_STREAM, 0)) == -1){
	perror("server : socket");
	return 1;
    }
    
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = INADDR_ANY;
    addr.sin_port = htons(atoi(argv[1]));
    
    // Connect port number and transport layer with socket
    if(bind(fd_socket, (struct sockaddr *)&addr, sizeof(addr)) == -1){
	    perror("server : bind");
	    return 1;
    }

    // Wait connection from client. The max number of client is 5
    if(listen(fd_socket, 5) == -1){
	    perror("server : listen");
	    return 1;
    }
    printf("server start ! \n");
    clilen = sizeof(cli_addr);

    // Server get ip address and port number from client
    // Server and client connected each other.
    if((fd_accept = accept(fd_socket, (struct sockaddr *)&cli_addr, &clilen)) == -1){
	    perror("server : accept");
	    return 1;
    }

    // Convert binary ip address to decimal number
    inet_ntop(AF_INET, &cli_addr.sin_addr, buf, sizeof(buf));
    printf("client address => %s\n", buf);

    // Get data from client.
    // There are IP and PORT about client in fd_accept so it must be used.
    if(read(fd_accept, buffer, BUFSIZ) == -1){
	    perror("server : read");
	    return 1;
    }
    printf("receive message from client => %s\n", buffer);

    // Add string back of buffer
    strcat(buffer, " is returned message.");
    
    // Send data to client
    if(write(fd_accept, buffer, strlen(buffer) + 1) == -1){
    	perror("server: write");
	return 1;
    }

    // close the sockets in file descriptor
    close(fd_accept);
    close(fd_socket);
    return 0;
}
