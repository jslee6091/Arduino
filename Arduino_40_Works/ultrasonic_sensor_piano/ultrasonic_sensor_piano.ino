// 초음파센서 활용하여 거리 계산
// 거리에 따라 다른 음을 내도록 구현
#define PIEZO 10

// 초음파센서의 echo, trig 핀과 연결할 아두이노 핀 번호 설정
int echo = 6;
int trig = 7;
/*
  초음파센서는 echo, trig 핀을 이용하여 물체와의 거리를 계산한다.
  trig 에서 초음파가 전송되어 물체를 맞고 다시 되돌아와서 echo에 전달된다.
  echo는 trig 에서 초음파가 전송된 후 돌아올때까지 시간을 측정하여 거리를 계산한다.
*/

void setup() {
  Serial.begin(9600);
  // trig 핀은 출력, echo 핀은 입력
  pinMode(trig, OUTPUT);
  pinMode(echo, INPUT);
  pinMode(PIEZO, OUTPUT); // 생략해도 상관없음
}

void loop() {
  digitalWrite(trig, LOW);
  delayMicroseconds(2);
  // trig 핀을 HIGH로 설정하면 초음파센서의 trig 핀이 0V가 된다.
  digitalWrite(trig, HIGH);
  // 10uS 동안 delay
  delayMicroseconds(10);
  // trig 핀을 LOW로 설정 -> 초음파센서의 trig 핀이 5V가 됨
  digitalWrite(trig, LOW); 

  // echo핀이 HIGH값이 될때까지 시간을 저장
  unsigned long duration = pulseIn(echo, HIGH);

  // 초음파가 갔다오는데 걸린 시간과 음파의 속력을 이용하여 실제 물체와의 거리 계산
  float distanceCM = ((34000 * duration) / 1000000) / 2;

  Serial.println(distanceCM);

  if(distanceCM >= 0 && distanceCM < 10){
    tone(PIEZO, 262); // 도
  }
  else if(distanceCM >= 10 && distanceCM < 20){
    tone(PIEZO, 294); // 레
  }
  else if(distanceCM >= 20 && distanceCM < 30){
    tone(PIEZO, 329.6); // 미
  }
  else if(distanceCM >= 30 && distanceCM < 40){
    tone(PIEZO, 349.2); // 파
  }
  else if(distanceCM >= 40 && distanceCM < 50){
    tone(PIEZO, 392); // 솔
  }
  else if(distanceCM >= 50 && distanceCM < 60){
    tone(PIEZO, 440); // 라
  }
  else if(distanceCM >= 60 && distanceCM < 70){
    tone(PIEZO, 493.9); // 시
  }
  else if(distanceCM >= 70 && distanceCM < 80){
    tone(PIEZO, 523); // 도
  }
  else{
    noTone(PIEZO);
  }
  
  delay(100);
}
