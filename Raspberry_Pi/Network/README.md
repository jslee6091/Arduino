### 라즈베리파이3 네트워크 프로그래밍

- 이용진 저
- 복두 출판사
- 책 내용 Studying(Network Programming)

### 

### Chapter3

- Network Programming Basic
- Socket API
  - 응용 프로그램에서 데이터 송수신을 위한 system call
- TCP Socket Programming
- UDP Socket Programming
- Iterative server



### Chapter4

- Parallel Server
- 프로세스 생성
  - `fork()` system call
  - parent process
  - child process
- 스레드 생성
  - `pthread`
- 입출력 다중화
  - `select()`
  - `fd_set` 구조체



### Chapter5

- IP address
- Network 분할, subnet mask
- Socket option
  - `getsockopt()`
  - `setsockopt()`
- Broadcast
  - UDP socket
  - sender
  - receiver
- Multicast
  - UDP socket
  - sender
  - receiver
  - multicast group



### Chapter6

- Low level programming
- Protocol header
  - TCP, UDP, IP, Ethernet
  - architecture of each headers
- UDP pesudo header
- checksum
- SOCK_RAW
  - TCP or UDP 거치지 않고 바로 IP or Data Link(Ethernet) 계층에 접근
  - SOCK_PACKET 도 있음
- Packet capture
  - raw socket
  - packet capture & analysis
  - output the protocol headers(TCP, IP, Ethernet)

