// PC와 아두이노 사이의 시리얼 통신을 활용한 LED 제어 코드

void setup() {
  // 통신 속도 9600 bps로 설정
  Serial.begin(9600);
  pinMode(8, OUTPUT);
}

void loop() {
  // 받은 데이터의 개수가 있을 때(1 이상일 때)
  if (Serial.available() > 0){
    // Serial 데이터 read
    char sData = Serial.read();
    // PC에서 a, b, c를 보낸 경우 각각의 코드
    if (sData == 'a'){
      digitalWrite(8, HIGH);
    }
    else if (sData == 'b'){
      digitalWrite(8, LOW);
    }
    else if (sData == 'c'){
      digitalWrite(8, HIGH);
      delay(1000);
      digitalWrite(8, LOW);
      delay(1000);
    }
  }
}
