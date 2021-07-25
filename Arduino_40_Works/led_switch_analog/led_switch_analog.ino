// 스위치 클릭 횟수마다 LED 밝기가 커지도록 만들기
#define SWITCH 3
#define LED 11

int newSWvalue = 1;
int oldSWvalue = 1;

// 스위치 클릭 횟수
int cnt = 0;

void setup() {
  pinMode(SWITCH, INPUT_PULLUP);
}

void loop() {
  newSWvalue = digitalRead(SWITCH);

  // 이전 스위치 값과 현재 스위치 값이 다른 경우(스위치가 눌렸거나 떼어졌을 때)
  if (newSWvalue != oldSWvalue){
    // 현재 스위치 값 입력
    oldSWvalue = newSWvalue;
    // 1 -> 0 으로 바뀐 경우 (스위치가 눌렸을 때)
    if(oldSWvalue == 0){
      // 스위치 클릭 횟수 1 증가
      cnt++;
      // 4 이상인 경우 0으로 초기화 - LED 밝기는 4단계로 분류했기 때문
      if(cnt >= 4){
        cnt = 0;
      }
      delay(200);
    }
  }

  // 현재 cnt 값에 따라 LED가 서로 다른 밝기를 가지도록 핀에 write
  analogWrite(LED, 50 * (cnt + 1));
  /*
  원래의 예제 코드인데 위의 것으로 변형해봤다.
  if(cnt == 0){
    analogWrite(LED, 50);
  }
  else if(cnt == 1){
    analogWrite(LED, 100);
  }
  else if(cnt == 2){
    analogWrite(LED, 150);
  }
  else if(cnt ==3){
    analogWrite(LED, 255);
  }
  */
}
