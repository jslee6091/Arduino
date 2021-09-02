1. robot.c
   - 웹 서버에 접속하여 홈페이지를 가져와서 화면에 나타내는 프로그램
   - Compile : `$ gcc -o robot robot.c`
   - Execute : `./robot www.knue.co.kr smain.html`
   - 다른 임의의 사이트도 가능
2. tcp_client.c
   - TCP 프로토콜을 이용한 클라이언트 프로그램
   - 서버에 메시지 전송 후 다시 수신받음
   - Compile : `$ gcc -o tcp_client tcp_client.c`
   - Execute : `$ ./tcp_client 127.0.0.1 3000`
     - 원래 책에서는 `home.knue.ac.kr`으로 설정하도록 했지만 아래의 tcp 서버가 로컬환경에서 동작하므로 127.0.0.1로 했다.
     - 포트번호는 3000 이외에 다른 번호도 가능(단, 서버와 맞춰야 함)
3. tcp_server.c
   - TCP 프로토콜을 이용한 서버 프로그램
   - 클라이언트로부터 수신한 메시지를 확인 후 다시 클라이언트에 전송
   - Compile : `$ gcc -o tcp_server tcp_server.c`
   - Execute : `$ ./tcp_server 3000`
4. udp_client.c
   - UDP 프로토콜을 이용한 클라이언트 프로그램
   - 서버에 메시지 전송 후 다시 수신받음
   - Compile : `$ gcc -o udp_client udp_client.c`
   - Execute : `$ ./udp_client 127.0.0.1 3000`
5. udp_server.c
   - UDP 프로토콜을 이용한 서버 프로그램
   - 클라이언트로부터 수신한 메시지를 확인 후 다시 클라이언트에 전송
   - Compile : `$ gcc -o udp_server udp_server.c`
   - Execute : `$ ./udp_server 3000`
6. iterative_client.c
   - 반복형 채팅 서버에 접속하는 클라이언트
   - 하나의 클라이언트만 서버에 접근하여 채팅 가능
   - Compile : `$ gcc -o iterative_client iterative_client.c`
   - Execute : `$ ./iterative_client 127.0.0.1 3000`
7. iterative_server.c
   - 반복형 채팅 서버
   - 하나의 클라이언트만 접속 허용
   - Compile : `$ gcc -o iterative_server iterative_server.c`
   - Execute : `$ ./iterative_server 3000`

