//-----------------------
// multicast_receiver.c
// For multicast communication, it should join the multicast group address
// Sender sends data on the multicast tree.
// Receiver connected to the multicast tree and can receive data from sender
// So it's important to make efficient tree
//-----------------------
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
    int port;
    int set = 1;
    char message[256]; 					// 수신 메시지
    int messageLen;
    struct ip_mreq multi_group; 				// 멀티캐스트 그룹

    if (argc != 3) {   
        printf("Usage: %s <multicast_IP> <port>\n", argv[0]);
        return -1;
    }

    multi_IP = argv[1];
    port = atoi(argv[2]);

    if ((sock_fd = socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP)) < 0) {
        perror("socket() failed");
        return -1;
    }

    // 소켓 재사용
    setsockopt(sock_fd, SOL_SOCKET, SO_REUSEADDR, (void*)&set, sizeof(set));
    memset(&multi_addr, 0, sizeof(multi_addr));
    multi_addr.sin_family = AF_INET;
    multi_addr.sin_addr.s_addr = htonl(INADDR_ANY); 
    multi_addr.sin_port = htons(port);

    if (bind(sock_fd, (struct sockaddr *) &multi_addr, sizeof(multi_addr)) < 0){
        perror("bind() failed");
        return -1;
    }

    // 멀티캐스트주소 
    multi_group.imr_multiaddr.s_addr = inet_addr(multi_IP); 
    multi_group.imr_interface.s_addr = htonl(INADDR_ANY);	//자신의 IP주소

    // 멀티캐스트그룹에 가입
    if (setsockopt(sock_fd, IPPROTO_IP, IP_ADD_MEMBERSHIP, (void *)&multi_group, sizeof(multi_group)) < 0){
        perror("setsockopt() failed");
        return -1;
    }

    // 서버로부터 데이터그램 수신
    if ((messageLen = recvfrom(sock_fd, message, 255, 0, NULL, 0)) < 0){
        perror("recvfrom() failed");
        return -1;
    }

    message[messageLen] = '\0';
    printf("수신메시지: %s\n", message);
 
    close(sock_fd);
    return 0;
}
