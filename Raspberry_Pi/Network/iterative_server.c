// Chatting server using TCP
// Iterative server can accept only one client
#include <stdio.h>
#include <string.h>
#include <signal.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

char *escapechar = "exit\n";

int main(int argc, char *argv[]){
    int servfd, clifd, num, size, clilen;
    pid_t pid;
    struct sockaddr_in servaddr, cliaddr;
    char *haddr;
    char sbuf[BUFSIZ], rbuf[BUFSIZ];

    if(argc < 2){
        printf("Usage : %s TCP_PORT\n", argv[0]);
        return -1;
    }
    
    // Socket system call
    if((servfd = socket(AF_INET, SOCK_STREAM, 0)) < 0){
        perror("server : socket");
        return -1;
    }
    
    // clear servaddr
    bzero((char *)&servaddr, sizeof(servaddr));
    
    // servaddr setting
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(atoi(argv[1]));

    // bind the socket name
    if(bind(servfd, (struct sockaddr *)&servaddr, sizeof(servaddr)) < 0){
        perror("server: bind");
        return -1;
    }
    printf("Server started.\nWaiting for client...\n");

    // listen connection request from client
    listen(servfd, 5);
    clilen = sizeof(cliaddr);

    // accept the connection request from client
    if((clifd = accept(servfd, (struct sockaddr *)&cliaddr, &clilen)) != -1){
        printf("Server: client connected.\n");
    }
    else{
        perror("server: accept");
        return -1;
    }
    
    if((pid = fork()) > 0){
        while(fgets(sbuf, sizeof(sbuf), stdin) != 0){
            size = strlen(sbuf);
            if(write(clifd, sbuf, size) != size){
                perror("server: write");
                return -1;
            }

            if(size == 5 && strncmp(sbuf, escapechar, 4) == 0){
                // escape string
                kill(pid, SIGQUIT);
                exit(0);
            }
            
        }
    }
    // child process
    else if(pid == 0){
        while (1)
        {
            if((size = read(clifd, rbuf, BUFSIZ)) > 0){
                rbuf[size] = '\0';
                if(strncmp(rbuf, escapechar, 4) == 0){
                    break;
                }
                printf("%s", rbuf);
            }
        }
        
    }
    
    close(servfd);
    return 0;
}
