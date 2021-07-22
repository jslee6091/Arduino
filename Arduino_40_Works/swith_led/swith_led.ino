// 스위치를 입력으로 받아서 LED 켜기

#define BUTTON 4
#define LED 2

void setup() {
  Serial.begin(9600);
  // 4번핀을 입력 핀으로 설정 - 이곳을 스위치와 연결
  pinMode(BUTTON, INPUT_PULLUP);
  /*
    풀업 입력으로 설정한 이유 :
    아두이노 칩 내부의 풀업 저항으로 인해
    발생하는 애매한 상태인 플로팅 상태를 없애서
    0과 1을 정확히 알기 위함
  */
  pinMode(LED, OUTPUT);
}

void loop() {
  // 스위치로부터 오는 데이터 read - 스위치가 ON 일때 0 전송, OFF 일때 1 전송
  // 스위치가 GND와 연결되어있으므로 누르면 0이 된다.
  int buttonValue = digitalRead(BUTTON);
  // 눌렀을 때 LED 켜기
  if (buttonValue == 0){
    digitalWrite(LED, HIGH);
  }
  else{ // 그렇지 않으면 소등
    digitalWrite(LED, LOW);
  }
}
