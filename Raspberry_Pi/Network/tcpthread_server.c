//------------------------------------
//   tcpthread_server.c (multi_thread)
//   client : tcp_client.c
//   compile option : -lpthread
//   Server can accept several clients at the same time 
//   Client sends data to server, receive data from server and terminate
//------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include <errno.h>
#include <wait.h>
#include <sys/file.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <pthread.h> 			// POSIX thread header file
       
void *sub(void *);				// 스레드 함수 원형
int main(int argc, char *argv[])    
{    
    int server_sock;                    
    int client_sock;                   
    struct sockaddr_in server_addr;     
    struct sockaddr_in client_addr;     
    unsigned short server_port;         
    unsigned int caddr_len;          
    char msg_buf[BUFSIZ+1];          
    int  msg_size;                     
    int rc;  
    pthread_t threads; 			// 스레드 ID

    if (argc != 2)      
    {
        printf("Usage:  %s <Port>\n", argv[0]); 
        exit(1);
    }
    server_port = atoi(argv[1]);

    // PF_INET = AF_INET = TCP/IP(version 4)
    if ((server_sock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0)
    {
        perror("socket() failed");
        exit(1);
    }

    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    server_addr.sin_port = htons(server_port);

    if (bind(server_sock, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0){
        perror("bind() failed");
        exit(1);
    }

    if (listen(server_sock, 5) < 0){
        perror("listen() failed");
        exit(1);
    }

    printf("thread_server start !!\n");

    while(1)
    {
        caddr_len = sizeof(client_addr);
        if ((client_sock = accept(server_sock, (struct sockaddr *)&client_addr, &caddr_len)) < 0){
            perror("accept() failed");
            exit(1);
        }

        printf("Process = %d\n", getpid());
        printf("Echo request from %s\n", inet_ntoa(client_addr.sin_addr));
        // printf("client_sock = %d\n", client_sock);
        // thread number is threads and thread function is sub
	// client_sock is a parameter of sub function
        rc = pthread_create(&threads, NULL, sub, (void *)client_sock);
    }
}

void *sub(void *arg) 			// 스레드 함수
{
    // Client socket descriptor
    int csock = (int) arg;
    char msg_buf[BUFSIZ+1];
    int msg_size;

    printf("Process = %d Thread %d\n", getpid(), pthread_self());

    // receive data from client
    if(read(csock, msg_buf, BUFSIZ) == -1)
    {
        perror("Server: read");
        exit(1);
    }
    printf("receive message from client => %s\n", msg_buf);

    // send data to client
    strcat(msg_buf, " is returned message.");
    if (write(csock, msg_buf, strlen(msg_buf)+1) == -1)
    {
        perror("server: write");
        exit(1);
    }
    pthread_exit(NULL);
}
