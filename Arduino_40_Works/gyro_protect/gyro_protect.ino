// 가속도 센서를 이용하여 X축, Y축 값을 측정하여 시리얼 플로터에서 확인하기
// MPU6050 센서를 사용하기 위한 MPU6050_tockn 라이브러리
// 이것 외에도 다양한 라이브러리가 있다.
#include <MPU6050_tockn.h>
#include <Wire.h>

/*
  가속도센서는 VCC, GND, SDA, SCL 핀 사용하여 연결
  I2C 통신을 따라 SDA는 아두이노의 A4 핀, SCL는 아두이노의 A5 핀과 연결
*/

MPU6050 mpu6050(Wire);                // mpu6050이름의 클래스 생성

void setup() {
  Serial.begin(9600);
  Wire.begin();
  mpu6050.begin();                    // mpu6050 센서 초기화(몇초간 센서 보정 진행)
  mpu6050.calcGyroOffsets(false);     // 보정값 출력x
}

void loop() {
  mpu6050.update();                   // 값을 업데이트
  Serial.print("X : ");
  Serial.print(mpu6050.getAccX());    // 가속도 X 값 전송
  Serial.print("\tY : ");
  // 시리얼 플로터에서 확인하기 위해서는 다음줄로 넘기는 작업이 필요하다.
  Serial.println(mpu6050.getAccY());  // 가속도 Y 값 전송
}
