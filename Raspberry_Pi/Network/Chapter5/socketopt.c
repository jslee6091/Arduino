//-------------------------------------------------------
// socketopt.c  (소켓 옵션 사용하기)
// Compile: $ gcc -o socketopt.c -o socketopt
// Execute: $ ./socketopt
//-------------------------------------------------------
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>

/*
  int setsockopt(
  	int socket,			// Socket descriptor
	int level,			// Protocol level
	int option_name,		// Option name
	const void *option_val,		// Pointer of option
	unsigned int option_len		// Byte of variable of option
  )

  int getsockopt(
  	int socket,			// Socket descriptor
	int level,			// Protocol level
	int option_name,		// Option name
	void *option_val,		// Pointer of option
	unsigned int option_len		// Byte of variable of option
  )
*/

int main(){
    int s;
    int val, len; 			// 수신버퍼
    int ttl, optlen; 			// TTL
    int set = 1;			// 주소 (포트)의 재사용
    
    if ((s = socket(AF_INET, SOCK_STREAM, 0)) < 0){
        perror("socket fail");
        return -1;
    }
    
    // 버퍼의 크기를 알아내고 수정하기
    len = sizeof(val);
    if (getsockopt(s, SOL_SOCKET, SO_RCVBUF, &val, &len) < 0){
        perror("socket fail");
        return -1;
    }
    printf("현재 수신버퍼 크기: %d\n", val);

    val = 2144;
    setsockopt(s, SOL_SOCKET, SO_RCVBUF, &val, sizeof(val));
    getsockopt(s, SOL_SOCKET, SO_RCVBUF, &val, &len);
    printf("변경 수신버퍼 크기: %d\n", val);

    // IP헤더의 TTL 값 알아내고 변경하기
    getsockopt(s, IPPROTO_IP, IP_TTL, &ttl, &optlen);
    printf("현재 TTL = %d\n", ttl);
    
    ttl = 32;
    setsockopt(s, IPPROTO_IP, IP_TTL, &ttl, sizeof(ttl));
    printf("변경 TTL = %d\n", ttl);

    // 주소(포트 번호 등) 재사용하기
    setsockopt(s, SOL_SOCKET, SO_REUSEADDR, (void*)&set, sizeof(int));
    return 0;
}
