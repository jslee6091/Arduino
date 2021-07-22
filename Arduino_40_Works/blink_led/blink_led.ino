#define LED1 10
#define LED2 8
#define DELAY_TIME 200

// LED 2개가 서로 번결아가며 점멸을 반복하는 코드
void setup() {
  // 핀 번호 설정
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
}

void loop() {
  // 두 LED가 일정 시간을 두고 점멸을 반복함
  digitalWrite(LED1, LOW);
  digitalWrite(LED2, HIGH);
  delay(DELAY_TIME);
  digitalWrite(LED1, HIGH);
  digitalWrite(LED2, LOW);
  delay(DELAY_TIME);
}
