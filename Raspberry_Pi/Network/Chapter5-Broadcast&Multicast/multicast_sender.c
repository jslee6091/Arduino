//--------------------
// multicast_sender.c
//--------------------
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>

int main(int argc, char *argv[]){
    int sock_fd;
    struct sockaddr_in multi_addr;
    char *multi_IP;
    int  port;
    char *message;
    unsigned char TTL = 5; 		// 멀티캐스트 패킷의 TTL
    unsigned int messageLen;

    if (argc !=4){
        printf("Usage:  %s <multicast_address> <port> <message>\n", argv[0]);
        return -1;
    }

    multi_IP = argv[1];
    port = atoi(argv[2]);
    message = argv[3];

    if ((sock_fd = socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP)) < 0){
        perror("socket() failed");
        return -1;
    }
    
    if (setsockopt(sock_fd, IPPROTO_IP, IP_MULTICAST_TTL, (void *) &TTL, sizeof(TTL)) < 0){
        perror("setsockopt() failed");
        return -1;
    }

    memset(&multi_addr, 0, sizeof(multi_addr));
    multi_addr.sin_family = AF_INET;
    multi_addr.sin_addr.s_addr = inet_addr(multi_IP);
    multi_addr.sin_port = htons(port);
    messageLen = strlen(message);
    
    while(1){
        /* 매 5초마다 메시지 전송 */
        if (sendto(sock_fd, message, messageLen, 0, (struct sockaddr *)&multi_addr, sizeof(multi_addr)) != messageLen){
            perror("sendto() error");
            return -1;
        }
        printf("송신메시지: %s\n", message);
        sleep(5);
    }
}