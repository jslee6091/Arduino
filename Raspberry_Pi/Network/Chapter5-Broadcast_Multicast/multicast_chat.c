//-------------------------------------------------------------
// multicast.c
// 멀티캐스트를 이용한 채팅 프로그램(스레드 사용)
// Compile: $ gcc multicast.c -o multicast -lpthread
// Execute: $ ./multicast 224.1.1.1 8900  NAME   
//-------------------------------------------------------------
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>

#define MAX_BYTES 1023

void *send_rtn(void *arg); 		// 송신 스레드
void *recv_rtn(void *arg); 		// 수신 스레드
char name[10]; 				// 채팅참가자 이름
int send_sock, recv_sock; 		// 소켓기술자
struct sockaddr_in group;  		// 멀티캐스트 그룹주소
struct ip_mreq interface; 		// 인터페이스 주소

int main(int argc, char *argv[]){
    pthread_t tid1, tid2; 			// 스레드 번호
    unsigned int on = 1;
    int TTL = 1; 				// 생존시간(hop)
    u_char mcTTL;

    if (argc != 4) {
        printf("사용법: %s multicast_address port name \n", argv[0]);
        return -1;
    }

    sprintf(name, "[%s]", argv[3]); 		// 채팅 참가자 이름

    // 멀티캐스트 수신용 소켓 개설
    memset(&group, 0, sizeof(group));
    group.sin_family = AF_INET;
    group.sin_port = htons(atoi(argv[2]));
    inet_pton(AF_INET,argv[1],&group.sin_addr);

    if ( (recv_sock=socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
        perror("socket() failed\n");
        return -1;
    }

    // 멀티캐스트 그룹에 가입
    interface.imr_multiaddr = group.sin_addr;
    interface.imr_interface.s_addr = htonl(INADDR_ANY);

    if (setsockopt(recv_sock, IPPROTO_IP, IP_ADD_MEMBERSHIP, &interface, sizeof(interface)) < 0){
        perror("join group failed\n");
        return -1;
    }

    // 소켓 재사용 옵션 지정
    if (setsockopt(recv_sock, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on)) < 0){
        perror("setsockopt() failed\n");
        return -1;
    }

    // 바인딩
    if (bind(recv_sock, (struct sockaddr*)&group, sizeof(group)) < 0){
        perror("bind() failed\n");
        return -1;
    }

    // 멀티캐스트 메시지 송신용 소켓 개설
    if ((send_sock=socket(AF_INET, SOCK_DGRAM, 0)) < 0){
        perror("socket() failed\n");
        return -1;
    }

    // 송신용 소켓의 TTL 설정
    mcTTL = (u_char) TTL;
    if(setsockopt(send_sock, IPPROTO_IP, IP_MULTICAST_TTL, &mcTTL, sizeof(mcTTL)) < 0){
        perror("ttl setsockopt() failed\n");
        return -1;
    }

    // 송신스레드 생성
    if (pthread_create(&tid1, NULL, send_rtn, NULL) != 0){
        perror("thread create error\n");
        return -1;
    }

    // 수신스레드 생성
    if(pthread_create(&tid2, NULL, recv_rtn, NULL) != 0){
        perror("thread create error\n");
        return -1;
    }

    pthread_join(tid1, NULL); 		// 송신 스레드 종료까지 기다림
    pthread_join(tid2, NULL); 		// 수신 스레드 종료까지 기다림
    return 0;
}

void *recv_rtn(void *arg){ 		// 수신 스레드 및 화면 출력
    struct sockaddr_in from;
    char recv_message[MAX_BYTES+1];
    int n, length;

    while (1){
        length = sizeof(from);
        if ((n=recvfrom(recv_sock, recv_message, MAX_BYTES, 0, (struct sockaddr*)&from, &length)) < 0){
            perror("recvfrom() failed\n");
            exit(1);
        }
        recv_message[n] = 0;
        printf("%s\n", recv_message);
    }
}

void *send_rtn(void *arg){ 		//키보드 입력 및 송신 스레드
    char message [MAX_BYTES+1], send_line[MAX_BYTES+1];
    int len;

    while (fgets(message, MAX_BYTES, stdin) != NULL){
        sprintf(send_line, "%s %s", name, message);
        len = strlen(send_line);

        if(sendto(send_sock, send_line, strlen(send_line), 0, (struct sockaddr*)&group, sizeof(group)) < len){
            perror("sendto() failed\n");
            exit(1);
        }
    }
}