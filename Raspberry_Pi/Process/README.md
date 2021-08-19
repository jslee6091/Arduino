### 파이프

> pipe.c



- IPC(Inter-Process Communication)의 한 종류
- 파일 디스크립터 기반의 IPC
- 단방향(one-way) 통신
- 부모 프로세스와 자식 프로세스 사이의 통신만 가능





### FIFO

> fifo_client.c
>
> fifo_server.c



- IPC(Inter-Process Communication)의 한 종류
- 파일 디스크립터 기반의 IPC
- 단방향(one-way) 통신
- 프로세스 사이에서 통신이 가능
- IPC 조인에 사용하는 이름이 있어서 `Named Pipe`라고도 함





### 메시지 큐

> msg_client.c
>
> msg_server.c



- 유닉스 시스템 V/XSI의 IPC 중 하나
- 프로세스 사이의 통신을 위해 입출력 데이터를 커널 내부의 메시지 리스트 형태로 보관
- 메시지가 중간에 저장되므로 보내는 프로세스와 받는 프로세스가 동일한 시점에 주고 받을 필요 없음
- 서버와 클라이언트는 동일한 키 값을 가짐





### POSIX IPC

1. POSIX 메시지 큐

   - `posix_msg_client.c` , `posix_msg_server.c`

   - 시스템 V의 함수는 시스템 콜인데 POSIX 함수는 라이브러리

   - 소스코드 빌드 시 rt(Realtime) 라이브러리 링크

     - ```
       gcc -o posix_msg_server posix_msg_server.c -lrt
       ```

2. POSIX 세마포어

   - `posix_sem.c`

   - 네임드 세마포어

   - 세마포어를 보다 쉽게 사용할 수 있는 라이브러리 함수

   - 소스코드 빌드 시 pthread 라이브러리 링크

     - ```
       gcc -o posix_sem posix_sem.c -pthread
       ```



### IPC 관련 명령어

1. ```
   $ ipcs
   ```

   - 유닉스 시스템 V의 설정된 IPC 채널 확인
   - 메시지 큐, 공유 메모리, 세마포어 전체 확인

2. ```
   $ ipcs -q
   ```

   - IPC 채널 중 메시지 큐만 확인

3. ```
   $ ipcs -m
   ```

   - IPC 채널 중 공유 메모리만 확인

4. ```
   $ ipcs -s
   ```

   - IPC 채널 중 세마포어만 확인

5. ```
   $ ipcmk
   ```

   - IPC 채널 생성
   - `-M size` 옵션 : 일정 크기의 공유 메모리 생성
   - `-S nsems` 옵션 : 세마포어 생성
   - `-Q` 옵션 : 메시지 큐 생성

6. ```
   $ ipcrm
   ```

   - IPC 채널 삭제

   - 만약 메시지큐 삭제 시 `-q` 옵션과 메시지 큐의 ID를 이용하여 삭제

   - ```
     $ ipcrm -q 819200
     ```

