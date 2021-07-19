### Arduino에서 FreeRTOS 사용해보기

1. Arduino IDE의 GUI 버전 실행
   - 아두이노 IDE 폴더에 있는 `arduino.exe` 더블 클릭
2. 스케치 -> 라이브러리 포함하기 -> 라이브러리 관리
3. FreeRTOS 검색 -> FreeRTOS by Phillip Stevens 선택 -> 최신 버전으로 설치
   - Phillip Stevens 에 의한 FreeRTOS 인데 앞으로 이름이 바뀔 수 있다.
   - 책에서는 Richard Barry 라고 나와있는데 그 이후에 이름이 바뀌었다.
4. Blink_AnalogRead 예제 실행
   - 파일 -> 예제 -> FreeRTOS -> Blink_AnalogRead 선택\
5. 아두이노 우노와 컴퓨터 연결
6. 아두이노에 접속한 포트 선택
   - 툴 -> 포트 -> 접속한 포트 클릭
7. 컴파일 실행
   - 스케치 -> 확인/컴파일 클릭
8. 업로드
   - 컴파일 후 보드에 기록함
   - 기록된 스케치가 아두이노 보드에서 바로 실행된다.
   - 1초 마다 아두이노 보드의 LED(Breadboard에 LED 소자 연결하는것 아님)가 점멸을 반복한다.
9. AD 변환 센서 값 모니터링
   - Tools -> Serial Monitor 클릭하면 AD 변환 센서의 값이 출력된다.





### FreeRTOS 동작

1. 구성

   - Task : 프로그램의 각 처리를 의미

     - 각 Task에는 TCB(Task Control Block) 라는 관리테이블과 스택이 있음

     - FreeRTOS는 타이머 인터럽트를 받을 때마다 Task 실행 순서 결정하고 실행할 Task를 전환한다.

   - 시스템 콜 : Task 관리 상태 변경, 데이터 송수신 제어

     - Task가 시스템 콜을 통해 실시간 운영체제에 우선순위 관리, 라운드 로빈(Round Robin), Task간 통신을 위한 Queue, Semaphore, 이벤트 플래그 등 여러 가지 처리를 요청할 수 있다.

   - 세마포어 : Task 간 동기화

     - Task끼리 같은 데이터 취급할 때 제어를 하기 위한 시스템 콜

2. 기본 동작

   - 4가지 상태를 가짐 - 대기(ready), 일시 중지(suspended), 블록(blocked), 실행(running)
     - 대기(ready) : Task 실행 준비를 할 수 있는 상태. 우선순위가 높은 Task가 동작하고 있지 않다면 현재 동작 중인 Task가 끝난 다음에 실행 상태가 될 수 있음
     - 실행(running) : Task를 실행하는 상태
     - 블록(blocked) : Task가 이벤트를 기다리는 상태. 이벤트 발생시 우선순위에 따라 대기 상태가 됨
     - 일시 중지(suspended) : Task가 중단되어 있는 상태. 재개(resume) 시스템 콜이 발행하면 복귀함
   - 타이머 인터럽트를 받으면 대기 상태의 Task 중 가장 우선순위 높은 것이 실행 상태로 바뀐다.
   - 라운드 로빈(Round Robin) 방식으로 Task가 실행된다.
   - 실행중인 Task가 대기를 해야 하는 시스템 콜을 실행하면 블록 상태로 전환되고 다음 Task가 실행 된다.
   - 블록 상태의 Task는 대기를 해제하는 시스템 콜이 실행되거나 대기 조건의 이벤트가 발생하면 대기 상태로 전환된다.
   - 실행중인 Task가 일시 중지 하는 시스템 콜을 실행하면 일시 중지 상태가 되고 새로운 Task가 실행된다.
   - 다시 실행상태로 돌아오려면 resume 시스템 콜이 실행되어야 한다.
   - 각 상태로 전환 위한 시스템 콜
     - vTaskSuspend(): Ready -> Suspended, Running -> Suspended, Blocked -> Suspended
     - vTaskResume(): Suspended -> Ready
     - xTaskCreate(): Ready로 설정
     - 이벤트 발생 : Blocked -> Ready
     - Blocking 함수 실행 : Running -> Blocked





### 소스 코드 분석을 통한 동작 확인

- Blink_AnalogRead 소스코드 분석

- > 출처 : https://github.com/feilipu/Arduino_FreeRTOS_Library/blob/master/examples/Blink_AnalogRead/Blink_AnalogRead.ino

- 전체 소스 코드

- ```c
  #include <Arduino_FreeRTOS.h>
  
  // define two tasks for Blink & AnalogRead
  void TaskBlink( void *pvParameters );
  void TaskAnalogRead( void *pvParameters );
  
  // the setup function runs once when you press reset or power the board
  void setup() {
    
    // initialize serial communication at 9600 bits per second:
    Serial.begin(9600);
    
    while (!Serial) {
      ; // wait for serial port to connect. Needed for native USB, on LEONARDO, MICRO, YUN, and other 32u4 based boards.
    }
  
    // Now set up two tasks to run independently.
    xTaskCreate(
      TaskBlink
      ,  "Blink"   // A name just for humans
      ,  128  // This stack size can be checked & adjusted by reading the Stack Highwater
      ,  NULL
      ,  2  // Priority, with 3 (configMAX_PRIORITIES - 1) being the highest, and 0 being the lowest.
      ,  NULL );
  
    xTaskCreate(
      TaskAnalogRead
      ,  "AnalogRead"
      ,  128  // Stack size
      ,  NULL
      ,  1  // Priority
      ,  NULL );
  
    // Now the task scheduler, which takes over control of scheduling individual tasks, is automatically started.
  }
  
  void loop()
  {
    // Empty. Things are done in Tasks.
  }
  
  /*--------------------------------------------------*/
  /*---------------------- Tasks ---------------------*/
  /*--------------------------------------------------*/
  
  void TaskBlink(void *pvParameters)  // This is a task.
  {
    (void) pvParameters;
  
  /*
    Blink
    Turns on an LED on for one second, then off for one second, repeatedly.
  
    Most Arduinos have an on-board LED you can control. On the UNO, LEONARDO, MEGA, and ZERO 
    it is attached to digital pin 13, on MKR1000 on pin 6. LED_BUILTIN takes care 
    of use the correct LED pin whatever is the board used.
    
    The MICRO does not have a LED_BUILTIN available. For the MICRO board please substitute
    the LED_BUILTIN definition with either LED_BUILTIN_RX or LED_BUILTIN_TX.
    e.g. pinMode(LED_BUILTIN_RX, OUTPUT); etc.
    
    If you want to know what pin the on-board LED is connected to on your Arduino model, check
    the Technical Specs of your board  at https://www.arduino.cc/en/Main/Products
    
    This example code is in the public domain.
  
    modified 8 May 2014
    by Scott Fitzgerald
    
    modified 2 Sep 2016
    by Arturo Guadalupi
  */
  
    // initialize digital LED_BUILTIN on pin 13 as an output.
    pinMode(LED_BUILTIN, OUTPUT);
  
    for (;;) // A Task shall never return or exit.
    {
      digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
      vTaskDelay( 1000 / portTICK_PERIOD_MS ); // wait for one second
      digitalWrite(LED_BUILTIN, LOW);    // turn the LED off by making the voltage LOW
      vTaskDelay( 1000 / portTICK_PERIOD_MS ); // wait for one second
    }
  }
  
  void TaskAnalogRead(void *pvParameters)  // This is a task.
  {
    (void) pvParameters;
    
  /*
    AnalogReadSerial
    Reads an analog input on pin 0, prints the result to the serial monitor.
    Graphical representation is available using serial plotter (Tools > Serial Plotter menu)
    Attach the center pin of a potentiometer to pin A0, and the outside pins to +5V and ground.
  
    This example code is in the public domain.
  */
  
    for (;;)
    {
      // read the input on analog pin 0:
      int sensorValue = analogRead(A0);
      // print out the value you read:
      Serial.println(sensorValue);
      vTaskDelay(1);  // one tick delay (15ms) in between reads for stability
    }
  }
  ```

  - Task 생성 부분
    - xTaskCreate() 사용
    - Task 생성 시 이름, 스택 크기, 우선순위를 등록(우선 순위는 숫자가 클 수록 높음)
    - TaskBlink()와 TaskAnalogRead() 2개의 Task 생성하며 우선 순위는 TaskBlink()가 더 높음
    - 생성 시 대기 상태가 됨
  - TaskBlink()
    - LED 점등, 소등 시키는 처리 실행
    - 1초마다 점등과 소등이 반복됨
    - vTaskDelay()를 통해 Task는 1초간 중단되고 블록 상태로 전환됨.
  - TaskAnalogRead()
    - 직렬 포트 출력 Task
    - 하드웨어의 AD 변환 센서를 읽어서 결과를 직렬 포트에 출력
    - 15ms 동안 블록 상태가 되고 그 이후 대기 상태로 전환
    - TaskBlink()가 블록 상태이면 곧바로 실행 상태로 전환되어 센서 값 읽음
  - TaskBlink()와 TaskAnalogRead()가 함께 동작하면서 대기, 실행, 블록 상태가 반복된다. 이때 TaskBlink()의 우선순위가 더 높으므로 둘 다 대기상태에 있을 때는 TaskBlink()가 먼저 실행된다.