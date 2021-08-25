// parallel server by making processes
// process is made by fork() system call
// the client is tcp_client.c
#include <stdio.h>
#include <string.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <wait.h>
#include <sys/file.h>
#include <sys/socket.h>
#include <arpa/inet.h>

void echo_message(int csock);

int main(int argc, char *argv[]){
    int servfd, clifd, size;
    unsigned short server_port;
    unsigned int caddr_len;
    pid_t pid;
    struct sockaddr_in servaddr, cliaddr;
    char *haddr;
    char sbuf[BUFSIZ], rbuf[BUFSIZ];

    if(argc != 2){
        printf("Usage : %s <Port>\n", argv[0]);
        return -1;
    }
    server_port = atoi(argv[1]);
    
    // Socket system call
    if((servfd = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0){
        perror("socket failed");
        return -1;
    }
    
    memset(&servaddr, 0, sizeof(servaddr));
    // servaddr setting
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(server_port);

    // bind the socket name
    if(bind(servfd, (struct sockaddr *)&servaddr, sizeof(servaddr)) < 0){
        perror("bind failed");
        return -1;
    }

    // listen connection request from client
    if(listen(servfd, 5) < 0){
        perror("listen failed");
        return -1;
    }
    printf("fork server start!!\n");

    while(1){
	caddr_len = sizeof(cliaddr);
	// accept the connection request from client
	if((clifd = accept(servfd, (struct sockaddr *)&cliaddr, &caddr_len)) < 0){
	    printf("accept() failed");
	    return -1;
    	}
	printf("Echo request from %s\n", inet_ntoa(cliaddr.sin_addr));
	printf("client_sock = %d\n", clifd);
    
    	if((pid = fork()) < 0){
	    perror("fork() failed");
	    return -1;
	}
	// child process
	if(pid==0){
	    // server socket doesn't need because child do only data sending/receiving 
	    close(servfd);
	    echo_message(clifd);
	    return -1;
	}
	// parent process
	// client socket doesn't need because parent do only connecting server and client
	close(clifd);
	printf("Parent Process %d\n", getpid());
    }
}

// child process send/receive data
void echo_message(int csock){
    char msg_buf[BUFSIZ + 1];
    int msg_size;
    printf("Child Process %d\n", getpid());
    if(read(csock, msg_buf, BUFSIZ) == -1){
	perror("server: read");
	exit(1);
    }
    printf("receive message from client => %s\n", msg_buf);
    strcat(msg_buf, " is returned message");
    if(write(csock, msg_buf, strlen(msg_buf)+1) == -1){
	perror("server: write");
	exit(1);
    }
}
