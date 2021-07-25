// 초음파센서 활용하여 거리 계산하기
int echo = 6;
int trig = 7;

void setup() {
  Serial.begin(9600);
  // trig 핀은 출력, echo 핀은 입력
  pinMode(trig, OUTPUT);
  pinMode(echo, INPUT);
}

void loop() {
  digitalWrite(trig, LOW);
  delayMicroseconds(2);
  digitalWrite(trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig, LOW);

  // echo핀이 HIGH값이 될때까지 시간을 저장
  unsigned long duration = pulseIn(echo, HIGH);

  // 초음파가 갔다오는데 걸린 시간과 음파의 속력을 이용하여 실제 물체와의 거리 계산
  float distanceCM = ((34000 * duration) / 1000000) / 2;

  Serial.println(distanceCM);
  delay(100);
}
