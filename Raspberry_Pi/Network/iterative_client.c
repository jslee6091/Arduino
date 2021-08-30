// Chatting client using TCP
// Iterative allow only one client access to server
// Execute : ./iterative_client 127.0.0.1 3000(Random port number)
// Server and client can chat each other without interruption

#include <stdio.h>
#include <string.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

// exit string
char *escapechar = "exit\n";

int main(int argc, char *argv[]){
    int sock, n, size, comp, port;
    pid_t pid;
    struct sockaddr_in servaddr;
    char *haddr;
    char sbuf[BUFSIZ], rbuf[BUFSIZ + 1];
    
    if(argc != 3){
        printf("Usage : %s SERVER_ADDRESS TCP_PORT\n", argv[0]);
        return -1;
    }

    else{
        haddr = argv[1];
        port = atoi(argv[2]);
    }
    
    // Socket system call
    if((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0){
        perror("client : socket");
        return -1;
    }
    
    // clear servaddr
    bzero((char *)&servaddr, sizeof(servaddr));
    
    // servaddr setting
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = inet_addr(haddr);
    servaddr.sin_port = htons(port);

    // connent to server
    if(connect(sock, (struct sockaddr *)&servaddr, sizeof(servaddr))== -1){
    	perror("client: connect");
        return -1;
    }

    printf("Connected to server ...\n");
    
    // parent process
    if((pid = fork()) > 0){
        // parent process send the input from keyboard to server
        printf("I'm parent, %d %d\n", getpid(), getppid());
        while(fgets(sbuf, BUFSIZ, stdin) != 0){
            if(strlen(sbuf) == 5 && strncmp(sbuf, escapechar, 4) == 0){
                // escape string
                kill(pid, SIGQUIT);
                exit(1);
            }
            size = strlen(sbuf);
            if(write(sock, sbuf, strlen(sbuf)) != size){
                perror("client: write");
                return -1;
            }
        }
    }
    // child process
    else if(pid == 0){
        // child process display the receiving message from server
        printf("I'm child, %d %d\n", getpid(), getppid());
        while (1)
        {
            if((size = read(sock, rbuf, BUFSIZ)) > 0){
                rbuf[size] = '\0';
                if(size == 5 && strncmp(rbuf, escapechar, 4) == 0){
                    // exit string
                    exit(1);
                }
                printf("%s", rbuf);
            }
        }
        
    }
    
    close(sock);
    return 0;
}
