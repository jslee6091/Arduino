//----------------------------------------------------
// chat_server.c
// client : chat_client.c
// 컴파일: $ gcc chat_server.c -o chat_server
// 실행: $ ./chat_server 8900(or random port number)
//----------------------------------------------------
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <fcntl.h>
#include <sys/socket.h>
#include <sys/file.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

int nfds;  				// 최대 소켓 번호 + 1
int number = 0;				// 참가자 수
int sock_no[64]; 				// 참가자 소켓 번호 목록
int initial_sock; 				// 서버의 접속 소켓
void del_user(int); 				// 탈퇴 처리
char init_msg[20]; 				// 접속 환영 메시지

int main(int argc, char *argv[])
{
    struct sockaddr_in server_addr;  
    struct sockaddr_in client_addr;
    int server_sock, client_sock;
    char buf[BUFSIZ];
    char message[BUFSIZ];
    int i, j, max, nbyte, addrlen;
    fd_set read_fds;

    if(argc != 2) {
        printf("usage:%s port\n", argv[0]);
        return -1;
    }

    server_sock = socket(AF_INET, SOCK_STREAM, 0);
    if(server_sock == -1) {
        perror("socket fail"); 
        return -1;
    }
    initial_sock = server_sock;

    bzero((char *)&server_addr, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    server_addr.sin_port = htons(atoi(argv[1]));

    if (bind(server_sock , (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0)
    {
        perror("bind fail");
        return -1;
    }

    listen(server_sock, 5);

    while(1)
    {
        FD_ZERO(&read_fds);
	// Set server_sock bit to 1 to recognize connect request from client
        FD_SET(server_sock, &read_fds);

        for(i=0; i<number; i++){
	    // Set sock_no[i] bit to 1, sock_no[i] is socket descriptor doing chatting
            FD_SET(sock_no[i], &read_fds);
        }

        // 최대 소켓 번호 찾기
        nfds = initial_sock;
        for (i=0; i < number; i++)
        {
            if (sock_no[i] > nfds )
            {
                nfds = sock_no[i];
            }
        }
        nfds = nfds + 1; 		// nfds 계산
        puts("wait for client");

        if(select(nfds, &read_fds, NULL, NULL, NULL) < 0)
        {
            perror("select fail");
            return -1;
        }

        if(FD_ISSET(server_sock, &read_fds))
        {
            addrlen = sizeof(client_addr);
            client_sock = accept(server_sock, (struct sockaddr *)&client_addr, &addrlen);
        
            if(client_sock == -1)
            {
                perror("accept fail");
                return -1;
            }
        
            // 새로운 참가자 추가 루틴
	    // inet_ntop : Convert binary IP address to decimal address
            inet_ntop(AF_INET, &client_addr.sin_addr, message, sizeof(message));
            printf("새로운 클라이언트 참가: %s\n",message);
            sock_no[number] = client_sock;
            number = number + 1;

            strcpy(init_msg, "환영: 채팅 서버\n");
            if(write(client_sock, init_msg, strlen(init_msg)) < 0)
            {
                perror("write error");
                return -1;
            }

            printf("%d번째 참가자 추가\n", number);
        }

        for(i = 0; i < number; i++) {
            if(FD_ISSET(sock_no[i], &read_fds)) {
                nbyte = read(sock_no[i], buf, 512);
        
                if(nbyte<= 0) {
                    del_user(i);  	// 탈퇴자 처리
                    continue;
                }
                buf[nbyte] = 0;

                // 종료문자 (exit) 처리
                if(strstr(buf, "exit") != NULL) {
                    del_user(i);  		// 탈퇴자 처리
                    continue;
		}
                // 모든 참가자에게 메시지 전송
                for (j = 0; j < number; j++)
                    write(sock_no[j], buf, strlen(buf));
                    printf("%s\n", buf);
            }
        }
    }  // end of while
    return 0;
}

// 채팅 탈퇴자 처리루틴
void del_user(int index)
{
    close(sock_no[index]);
 
    if(index != number-1){
        sock_no[index] = sock_no[number-1];
    }
 
    number = number-1;
    printf("참가자 1명 탈퇴: 현재 인원 = %d\n", number);
}
