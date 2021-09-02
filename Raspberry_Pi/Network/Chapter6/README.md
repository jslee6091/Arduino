1. checksum8.c
   - UDP, TCP, IP, Ethernet 등 여러 헤더의 비트와 데이터가 오류가 있는지 체크하는 checksum을 구하는 과정을 간략히 나타낸 것
   - 실제로는 이보다 복잡하다.
   - Compile : `$ gcc -o checksum8 checksum8.c`
   - Execute : `$ ./checksum8`
2. capture.c
   - packet capture program
   - raw socket을 이용하여 실제 패킷을 캡처하고 분석한 후 프로토콜 헤더를 출력
   - raw socket은 SOCK_RAW와 SOCK_PACKET이 있는데 여기서는 SOCK_RAW 사용
   - SOCK_RAW는 UDP를 통과하는 SOCK_DGRAM 또는 TCP를 통과하는 SOCK_STREAM과 달리 TCP/UDP를 통과하지 않고 곧바로 IP 또는 Data Link(Ethernet) 계층에 접근
   - Ethernet header, IP header, TCP header 순서로 캡처 및 분석하여 헤더를 출력
   - Compile : `$ gcc -o capture capture.c`
   - Execute : `$ ./capture`



##### 이번 chapter6은 아직 이해하기 힘들어 capture의 경우에는 실제 동작을 확인하지 못했다.

##### 공부가 더 필요한 부분인 것 같다.

