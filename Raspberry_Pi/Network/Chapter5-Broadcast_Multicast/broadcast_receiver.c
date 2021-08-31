//----------------------------
// broadcast_receiver.c (UDP)
//----------------------------
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>

int main(int argc, char *argv[]){
    int sock_fd;
    struct sockaddr_in broad_addr;
    int port;
    char message[256];
    int messageLen;
    unsigned int set = 1;

    if (argc != 2){
        printf("Usage: %s <broadcast_port>\n", argv[0]);
        return -1;
    }
    port = atoi(argv[1]);

    if ((sock_fd = socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP)) < 0){
        perror("socket() failed");
        return -1;
    }

    memset(&broad_addr, 0, sizeof(broad_addr));
    broad_addr.sin_family = AF_INET;
    broad_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    broad_addr.sin_port = htons(port);
    
    /* 소켓주소의 재사용 */
    setsockopt(sock_fd, SOL_SOCKET, SO_REUSEADDR, (void*) &set, sizeof(set));

    /* 방송 주소의 바인딩 */
    if (bind(sock_fd, (struct sockaddr *) &broad_addr, sizeof(broad_addr)) < 0){
        perror("bind() failed");
        return -1;
    }

    /* 서버로 부터 하나의 데이터그램을 수신 */
    if ((messageLen = recvfrom(sock_fd, message, 255, 0, NULL, 0)) < 0){
        perror("recvfrom() failed");
        return -1;
    }

    message[messageLen] = '\0';
    printf("수신메시지: %s\n", message);
    close(sock_fd);
    return 0;
}
