1. socketopt.c
   - 소켓 옵션 조회 및 변경
   - `getsockopt()`, `setsockopt()`
   - SOL_SOCKET, IPPROTO_IP, IPPROTO_TCP의 옵션들을 조회 및 새로 설정
   - Compile : `$ gcc -o socketopt socketopt.c`
   - Execute : `$ ./socketopt`
2. broadcast_sender.c
   - 방송주소(broadcast address)를 이용하여 동일한 Data Link내의 모든 호스트들에게 packet을 전송
   - UDP 사용
   - Compile : `$ gcc -o broadcast_sender broadcast_sender.c`
   - Execute : `$ ./broadcast_sender broadcast_address 3000 message`
     - broadcast_address : `$ ifconfig`명령어를 입력하면 출력되는 wlan0의 broadcast 주소
     - message : 전달하고자 하는 메시지
3. broadcast_receiver.c
   - broadcast_sender로부터 전송되는 데이터를 수신
   - 여러 개의 receiver가 sender에 접속하여 동시에 데이터 수신 가능
   - sender가 broadcast 주소가 아닌 다른 주소(localhost, IPv4 주소 등)로 설정하면 동시에 데이터 수신 불가
   - Compile : `$ gcc -o broadcast_receiver broadcast_receiver.c`
   - Execute : `$ ./broadcast_receiver 3000`
4. multicast_sender.c
   - multicast를 이용한 송신 프로그램
   - broadcast는 하나의 LAN 내에서만 통신이 되지만 multicast는 LAN을 넘어서도 통신 가능
   - 중간에 경유하는 router는 MRP(Multicast Routing Protocol) 실행
   - Compile : `$ gcc -o multicast_sender multicast_sender.c`
   - Execute : `$ ./multicast_sender multicast_address 3000 message`
     - multicast_address : 멀티캐스트 주소인 224.0.0.0 ~ 239.255.255.255 범위 내 임의의 주소
     - message : 전달하고자 하는 임의의 메시지
5. multicast_receiver.c
   - multicast_sender로부터 데이터 수신
   - 여러 receiver가 동시 수신 가능
   - sender의 주소가 멀티캐스트 주소의 범위를 벗어나면 데이터 수신이 불가능
   - Compile : `$ gcc -o multicast_receiver multicast_receiver.c`
   - Execute : `$ ./multicast_receiver multicast_address 3000`
     - multicast_address : sender와 일치하는 주소
6. multicast_chat.c
   - multicast를 이용한 채팅 프로그램
   - 서버와 클라이언트 구분 없이 송신과 수신을 수행하는 thread를 생성하여 사용
   - 여러 개의 프로그램이 동시에 실행되어 채팅이 가능함
   - Compile : `$ gcc -o multicast_chat multicast_chat.c`
   - Execute : `$ ./multicast_chat multicast_address 3000 name`
     - multicast_address : 224.0.0.0 ~ 239.255.255.255 범위의 멀티캐스트 주소
     - name : 채팅에 참가하는 본인의 이름(임의로 지정)

