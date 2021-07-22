// PC와 아두이노 사이의 Serial 통신 여부 확인

void setup() {
  // 통신 속도 설정 - 19200 bps 등 여러속도가 가능하나 보통 9600 bps로 많이 함
  Serial.begin(9600);
}

void loop() {
  // 아두이노에서 PC로 hello 문자열 보내기
  // PC에서 확인할 때 시리얼 모니터 창에서 통신 속도를 아두이노와 맞추어야 함
  Serial.println("hello");
  delay(1000);
}
