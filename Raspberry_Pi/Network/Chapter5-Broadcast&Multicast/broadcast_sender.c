//--------------------------
// broadcast_sender.c (UDP)
//--------------------------
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <arpa/inet.h>

int main(int argc, char *argv[]){
    int broad_sock;  
    struct sockaddr_in broad_addr; 
    char *broad_IP;  
    int  port;  
    char *message;
    int permission;
    int messageLen;

    if (argc < 4){
        printf("Usage:  $ <IP Address> <Port> <Message>\n", argv[0]);
        return -1;
    }
    
    broad_IP = argv[1]; 
    port = atoi(argv[2]); 
    message = argv[3]; 
    
    if ((broad_sock = socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP)) < 0){
        perror("broad_socket() failed");
        return -1;
    }

    /* 브로드캐스트를 허용하도록 소켓 옵션 변경 */
    permission = 1;
    if (setsockopt(broad_sock, SOL_SOCKET, SO_BROADCAST, (void *) &permission, sizeof(permission)) < 0){
        perror("socket() failed");
        return -1;
    }

    memset(&broad_addr, 0, sizeof(broad_addr));   
    broad_addr.sin_family = AF_INET;                 
    broad_addr.sin_addr.s_addr = inet_addr(broad_IP);
    broad_addr.sin_port = htons(port);         
    messageLen = strlen(message);  

    while(1){
        /* 매 5초마다 클라이언트에게 데이터그램을 송신 */
        if (sendto(broad_sock, message, messageLen, 0, (struct sockaddr *)&broad_addr, sizeof(broad_addr)) != messageLen){
            perror("sendto() failed");
            return -1;
        }
        sleep(5); 			// 5초간 대기
    }
    return 0;
}