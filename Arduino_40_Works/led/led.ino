// 하나의 LED가 점멸을 반복하는 코드

void setup() {
  // setup code, 한번만 실행됨
  // 핀 설정 - 8번 핀을 출력핀으로 설정
  pinMode(8, OUTPUT);
}

void loop() {
  // main code, 무한 반복 실행됨
  // 핀의 출력 상태 설정 - 8번 핀에 HIGH 값 출력하도록 설정
  digitalWrite(8, HIGH);
  // 1000 ms 만큼 시간 지연
  delay(1000);
  digitalWrite(8, LOW);
  delay(1000);
}
