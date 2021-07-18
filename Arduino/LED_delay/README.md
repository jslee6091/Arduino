### LED 점멸 시간 지정하기

> _delay_ms()를 사용하여 LED 점멸 타이밍을 조절



- `led_basic.c`에서 `for`문을 이용하여 점멸 타이밍을 제어
  - `for`문은 반복 횟수나 실행되는 명령의 클럭 수에 따라 시간이 변할 수 있다.
  - 또한 빌드 시 최적화 옵션 사용 불가
- `_delay_ms()`을 사용하면 타이밍을 정확하게 구현할 수 있다.



#### 빌드 절차

1. `ELF` 파일 작성

   - ```
     avr-gcc -Os -Wall -g -mmcu=atmega328p led_delay.c -o led_delay.elf
     ```

   - `_delay_ms()`를 사용하는 경우 최적화 옵션(`-Os`)을 붙이지 않으면 warning 메시지 출력

   - 그럼에도 아래와 같은 warning이 발생하였다. 이에 대한 이유는 잘 모르겠다.

   - ```
     led_delay.c: In function 'main':
     led_delay.c:9:10: warning: value computed is not used [-Wunused-value]
          DDRB != (1 << PB1);
     ```

   - 오류 해결!

   - 원인 : `DDRB != (1 << PB1);` 이 아니라 `DDRB |= (1 << PB1);` 이다. 즉, DDRB와 (1 << PB1)의 값을 OR 연산하는 것이다. 

   - 이렇게 하니 LED 불빛이 더 밝고 선명하게 들어온다.

2. `HEX` 파일 작성

   - ```
     avr-objcopy -I elf32-avr -O ihex led_delay.elf led_delay.hex
     ```

   - 아두이노 우노의 ATmega328P에 전송하기 위한 HEX 파일 작성

3. 아두이노 우노 포트로 전송

   - ```
     avrdude -C C:\arduino-1.8.15-windows가 있는 폴더 지정\arduino-1.8.15\hardware\tools\avr\etc\avrdude.conf -v -patmega328p -carduino -PCOM4 -b115200 -D -Uflash:w:led_delay.hex:i
     ```


4. LED가 일정 주기로 점멸한다.



#### delay 시간 차이

- 1초마다 점멸하도록 설정했는데(`_delay_ms(1000)`) 실제로 delay 시간을 측정해보니 1초보다 짧았다.
- 이것은 `F_CPU`와 관련이 있는데 아두이노 모듈이 가지고 있는 크리스탈의 주파수와 관련 있었다.
- 아두이노 모듈의 크리스탈의 주파수를 `#define F_CPU`을 통해 정해주어야 원래의 1초가 나오는 것 같다.
- 아직 자세히는 모르겠다.



