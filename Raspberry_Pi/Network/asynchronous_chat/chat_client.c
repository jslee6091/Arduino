//-----------------------------------------------------------------------
// chat_client.c - chat client program
// 컴파일: pi@netlab:∼ $ gcc chat_client.c -o chat_client
// 실행:  pi@netlab:∼ $ chat_client IP_address_of_server port_number name
//-----------------------------------------------------------------------
#include <stdio.h>
#include <signal.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
char *escapechar = "exit\n"; 		// 종료 문자열

int main(int argc, char *argv[])
{
    char sbuf[BUFSIZ+1], rbuf[BUFSIZ+1];
    char *haddr;
    char bufmsg[BUFSIZ];
    int n, size, port;
    pid_t pid;
    int sock;
    struct sockaddr_in server_addr;

    if(argc != 4)
    {
        printf("Usage : %s SERVER_ADDRESS TCP_PORT NAME\n", argv[0]);
        return -1;
    }

    else
    {
        haddr = argv[1];
        port = atoi(argv[2]);
    }

    /* create socket */
    if(( sock = socket(PF_INET,  SOCK_STREAM, 0 )) < 0 )
    {
        perror("socket fail");
        return -1;
    }

    /* server_addr clear */
    bzero((char *)&server_addr, sizeof(server_addr));

    /* server_addr setting */
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = inet_addr(haddr);
    server_addr.sin_port = htons(port);

    /* connect to server */
    if( connect(sock, (struct sockaddr *) &server_addr, sizeof(server_addr)) < 0)
    {
        perror("connect fail");
        return -1;
    }

    if((pid = fork()) > 0) 			// 부모 프로세스
    {
        /* parent process send the input from keyboard to server */
        while (fgets(bufmsg, BUFSIZ, stdin) != 0)
        {
            if( strlen(bufmsg) == 5 && strncmp(bufmsg, escapechar, 4) == 0)
            {
                /* escape string */
                kill(pid, SIGQUIT);
                exit(1);
            }

            sprintf(sbuf, "[%s] :", argv[3]);
            strcat(sbuf, bufmsg);
            size = strlen(sbuf);

            if(write(sock, sbuf, strlen(sbuf)) != size)
            {
                perror("write fail");
                return -1;
            }
        }
    }

    else if (pid == 0) 			// 자식 프로세스
    {
        /* child process display the receiving message from server */
        while(1)
        {
            if(( size = read(sock, rbuf, BUFSIZ)) > 0)
            {
               printf("%s", rbuf);
            }
        }  // end of while
    }
    close(sock);
}