// 웹 서버에 접속하여 홈페이지 가져와서 화면에 나타내는 프로그램

#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>

/*
    struct sockaddr_in{
        sa_family_t         sin_family;
        unsigned short int  sin_port;
        struct in_addr      sin_addr;
        unsigned char       sin_zero[8];
    }

    struct in_addr{
        unsigned long s_addr;
    }

    struct hostent{
        char *h_name;           // host의 공식이름
        char **h_aliases;       // host의 별명
        int h_addrtype;         // 주소유형 (IPv4 또는 IPv6)
        int h_length;           // 주소의 바이트 수
        char **h_addr_list;     // 주소들의 포인터를 저장한 배열에 대한 포인터
    }

    #define h_addr **h_addr_list[0]; // 포인터 배열의 첫 번째 요소
*/

int main(int argc, char *argv[]){
    int sock, result;
    struct sockaddr_in server;
    struct hostent* host_info;
    char buf[20];
    char request[80], ch;
    
    /* check input condition */
    if(argc < 2){
        puts("Usage : robot hostname <url>");
        return;
    }
    
    // DNS 서비스를 통해 호스트 이름을 IP 주소로 변환
    host_info = gethostbyname(argv[1]);
    if(host_info == NULL){
        printf("Host not found! : %s\n\r", argv[1]);
        return;
    }

    // 기억장소 server를 server의 크기만큼 0으로 초기화
    bzero((char *)&server, sizeof(server));
    // 주소 체계를 AF_INET(IPv4)로 설정
    server.sin_family = AF_INET;
    // host_info->h_addr을 server.sin_addr로 host_info->h_length 바이트 복사
    memcpy((char *)&server.sin_addr, host_info->h_addr, host_info->h_length);
    // htons함수는 호스트 저장 순서를 네트워크 바이트 순서로 변환(Big Endian)
    server.sin_port = htons(80); // 웹 서버의 포트번호 80

    // Socket 시스템 호출 - 성공 시 파일 디스크립터 반환
    sock = socket(AF_INET, SOCK_STREAM, 0); // SOCK_STREAM : TCP를 프로토콜로 사용
    // sin_addr에 있는 2진 IP 주소를 buf의 크기만큼 10진법으로 변환 후 buf에 저장
    // IPv4, IPv6 모두 가능
    inet_ntop(AF_INET, &server.sin_addr, buf, sizeof(buf));
    printf("Trying %s .. \n", buf);
    
    // 서버의 주소(&server)를 이용해 서버와 연결
    result = connect(sock, (struct sockaddr *)&server, sizeof(server));
    if(result == -1){
        printf("Connect failed : %s\n", argv[2]);
        return;
    }

    printf("Connected %s.\n", argv[1]);
    
    if(argv[2] == NULL){
        sprintf(request, "GET /index.html HTTP/1.1 \n\r\n\r");
    }
    else{
        sprintf(request, "GET /%s HTTP/1.1 \n\r\n\r", argv[2]);
    }
    //서버로 메시지 송신
    write(sock, request, strlen(request));

    // 서버로부터 메시지 수신
    // read는 이미 OS에 수신된 메시지를 클라이언트의 기억 공간으로 가져옴
    while(read(sock, &ch, 1) > 0){
        putchar(ch);
    }

    // socket 종료 - 이후 TCP 연결이 해제됨
    close(sock);
    return 0;
}