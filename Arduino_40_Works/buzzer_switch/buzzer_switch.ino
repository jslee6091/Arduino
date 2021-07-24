// switch와 piezo buzzer를 이용하여 서로 다른 음의 소리를 출력하는 예제
#define PIEZO_BUZZER 3
#define SW1 5
#define SW2 6
#define SW3 7

void setup() {
  Serial.begin(9600);
  pinMode(SW1, INPUT_PULLUP);
  pinMode(SW2, INPUT_PULLUP);
  pinMode(SW3, INPUT_PULLUP);
}

void loop() {
  // tone() : 특정 핀에 특정 주파수의 구형파를  발생시키는 함수
  // 특정음(도레미파 등)에 대한 주파수를 입력하면 buzzer에서 소리가 남
  
  if(digitalRead(SW1) == 0){ // 스위치는 누르면 0 출력
    tone(PIEZO_BUZZER, 349.2);
  }
  else if(digitalRead(SW2) == 0){
    tone(PIEZO_BUZZER, 293.6);
  }
  else if(digitalRead(SW3) == 0){
    tone(PIEZO_BUZZER, 329.6);
  }
  else{
  // noTone() : 주파수 출력 해제 함수
  // 이 함수를 실행하지 않으면 계속 소리가 남
    noTone(PIEZO_BUZZER);
  }
}
