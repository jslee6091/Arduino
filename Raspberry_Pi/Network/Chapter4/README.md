1. process_server.c
   - 프로세스 생성을 이용한 병행 서버
   - 여러 클라이언트가 서버에 동시 접속이 가능
   - 클라이언트 : tcp_client.c
   - 여러 클라이언트로부터 전송받은 메시지를 다시 전송
   - Compile : `$ gcc -o process_server process_server.c`
   - Execute : `$ ./process_server 3000`
2. non_thread.c
   - thread를 추가로 생성하지 않는 코드
   - pthread를 이용해 원래 생성되는 스레드(main 스레드)의 번호를 조회함
   - Compile : `$ gcc -o non_thread non_thread.c -lpthread`
   - Execute : `$ ./non_thread`
3. thread.c
   - thread를 추가로 생성하는 코드
   - pthread를 이용하여 5개의 스레드 추가로 생성
   - Compile : `$ gcc -o thread thread.c -lpthread`
   - Execute : `$ ./thread`
4. tcpthread_server.c
   - 스레드를 이용한 parallel server
   - 클라이언트는 tcp_client.c 사용
   - 스레드를 생성하여 여러 클라이언트의 접속을 accept
   - Compile : `$ gcc -o tcpthread_server tcpthread_server.c -lpthread`
   - Execute : `$ ./tcpthread_server 3000`
5. tcpselect_server.c
   - 입출력 다중화를 이용한 병행 서버
   - 클라이언트는 tcp_client.c 사용
   - 스레드나 프로세스를 생성하지 않고 여러 클라이언트에 대한 입출력을 블로킹 모드 없이 처리
   - `select()` , `fd_set` 이용
   - Compile : `$ gcc -o tcpselect_server tcpselect_server.c`
   - Execute : `$ ./tcpselect_server 3000`
6. async_client.c
   - `select()`를 응용한 TCP 채팅 클라이언트
   - async_server.c에 접속하여 채팅
   - 여러 클라이언트가 동시 접속 가능
   - Compile : `$ gcc -o async_client async_client.c`
   - Execute : `$ ./async_client 127.0.0.1 3000 name`
     - name은 자신의 이름이므로 임의의 이름으로 설정 가능
7. async_server.c
   - `select()`를 응용한 TCP 채팅 서버
   - 입출력 다중화를 통한 병행 서버
   - async_client.c 클라이언트 여러개의 접속을 처리하여 서로 채팅이 가능
   - Compile : `$ gcc -o async_server async_server.c`
   - Execute : `$ ./async_server 3000`

