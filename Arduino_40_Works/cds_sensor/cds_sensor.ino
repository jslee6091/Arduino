// 조도센서를 이용하여 빛의 밝기를 인식하고 일정 시간 이상 어두울 시 LED를 점등
#define LIGHT_CDS A0
#define LED 11

int cnt = 0;

void setup() {
  Serial.begin(9600);
  pinMode(LED, OUTPUT);
}

void loop() {
  // 조도센서는 아날로그 핀을 사용한다.
  // 조도센서와 연결된 핀으로부터 센서값 읽어옴
  int cdsValue = analogRead(LIGHT_CDS);
  Serial.println(cdsValue);

  // 센서값(cds 값)은 빛이 밝을수록 커진다.
  if( cdsValue <= 300){ // 어두울 때
    
    // 3초 이상 빛이 들어오지 않은 경우(cnt 3 이상) 계속 어둡다고 판단해 LED를 점등
    if(cnt >= 3){
      digitalWrite(LED, HIGH);
    }
    // 어두워진지 3초가 안됬을 때 cnt 1씩 증가
    else{
      cnt++;
    }
    delay(1000);
  }
  // 밝을 때 cnt 값 초기화하고 LED 소등
  else{
    cnt = 0;
    digitalWrite(LED, LOW);
  }
}
