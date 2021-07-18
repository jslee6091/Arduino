### LED ON/OFF 실습

> 아두이노 우노와 LED, 저항 소자를 사용하여 LED 점멸 시키기 실습



- 빌드 절차

  - ```
    avr-gcc -g -mmcu=atmega328p led.c -o led.elf
    ```

    - elf 파일 만들기
    - 최적화 옵션(-Os)을 부여하면 for문이 없어지므로 옵션 제거

  - ```
    avr-objcopy -I elf32-avr -O ihex led.elf led.hex
    ```

    - 아두이노 우노의 ATmega328P에 전송하기 위한 HEX 파일 작성

  - ```
    ardude -C C:\arduino-1.8.15-windows가 있는 폴더 위치\arduino-1.8.15\hardware\tools\avr\etc\avrdude.conf -v -patmega328p -carduino -PCOM4 -b115200 -D -Uflash:w:led.hex:i
    ```

    - 명령어 실행 시 아두이노와 PC를 연결해야 함

    - 실행 중 다음과 같은 오류 발생했다.

    - ```
      avrdude: ser_open(): can't open device "\\.\COM4": 지정된 파일을 찾을 수 없습니다.
      ```

    - 이는 아두이노를 연결을 하지 않았거나 연결된 장치의 포트를 잘못 입력한 경우 발생한다.

    - 장치의 포트 확인 방법 : `장치 관리자 -> 포트(COM & LPT) -> USB 직렬 장치(COM4)`

    - 이때 `COM4`가 포트 번호이다.



- 실행 결과 LED가 빠르게 ON/OFF를 반복했다.



#### 핀 번호

- 아두이노의 `~9`번 핀을 이용했는데 이 핀이 연결된 곳이 바로 ATmega328P의 15번핀(PB1)이다.
- 다른 핀을 사용하고 싶다면 데이터시트를 확인해서 연결하면 된다.
  - ex) `~10` 번 핀을 사용하고 싶은 경우 ATmega328P의 16번 핀(PB2)을 이용하면 된다.
  - 이때 소스코드에서도 PB1을 모두 PB2로 바꾸면 된다.

