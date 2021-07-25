#include <MPU6050_tockn.h>
#include <Wire.h>

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
  Serial.print(mpu6050.getAccX());
  Serial.print("\tY : ");
  Serial.println(mpu6050.getAccY());
  
}
