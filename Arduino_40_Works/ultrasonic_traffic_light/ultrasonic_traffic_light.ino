// 초음파센서, LED, 능동부저를 이용하여 신호등 만들기
// 빨간색, 초록색 LED가 일정 시간마다 반복하여 점등
// 빨간색일때 초음파센서를 이용하여 일정 거리 이상 가까워지면 경고음 내기
#define RED 10
#define GREEN 9
#define BUZZER 12

// 시간 계산을 위한 변수
unsigned long currTime = 0;
unsigned long prevTime = 0;

// LED의 점등 시간 계산 위한 변수
int cnt = 1;

int echo = 6;
int trig = 7;

// 경고음이 울리는지 여부를 결정하기 위한 변수
int stopNgo = 0;

void setup() {
  Serial.begin(9600);
  pinMode(RED, OUTPUT);
  pinMode(GREEN, OUTPUT);
  pinMode(BUZZER, OUTPUT);
  pinMode(echo, INPUT);
  pinMode(trig, OUTPUT);
}

void loop() {
  // 현재 시간 저장
  currTime = millis();
  // 이전 시간보다 1초 이상 차이나는 경우
  if(currTime - prevTime >= 1000){
    // 현재 시간으로 갱신 후 cnt값 1증가
    prevTime = currTime;
    cnt++;
    
    // cnt가 16 이상인 경우 다시 빨간색으로 바뀌어야하므로 1로 변경
    if(cnt >= 16){
      cnt = 1;
    }

    // 1이상 10 이하인 경우 빨간색 점등 - 10초간 점등
    if(cnt >= 1 && cnt <= 10){
      digitalWrite(RED, HIGH);
      digitalWrite(GREEN, LOW);
      // 가까이 오는 사람에 대한 경고등이 울려야 하므로 1로 변경
      stopNgo = 1;
    }
    // 11이상 15이하인 경우 초록색 점등 - 5초간 점등
    else if(cnt >= 11 && cnt <= 15){
      digitalWrite(RED, LOW);
      digitalWrite(GREEN, HIGH);
      // 경고등이 필요없음
      stopNgo = 0;
    }
  }

  // 초음파센서를 이용하여 거리 계산
  float distance = ultraSonic();
  // 현재 빨간불이고 거리가 10 이하인 경우(도로와 가까운 경우) 경고음 울림
  if(distance <= 10 && stopNgo == 1){
    digitalWrite(BUZZER, HIGH);
  }
  else{
    digitalWrite(BUZZER, LOW);
  }
}

// 초음파센서를 통해 거리 계산
float ultraSonic(){
  digitalWrite(trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig, LOW);

  unsigned long duration = pulseIn(echo, HIGH);

  float distanceCM = ((340 * duration) / 10000) / 2;

  return distanceCM;
}
