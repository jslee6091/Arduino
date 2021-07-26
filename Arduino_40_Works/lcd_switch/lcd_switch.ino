// 2명의 플레이어가 각자의 스위치를 30초 동안 많이 누르기 게임
// 누른 횟수와 경과 시간을 I2C LCD 보여줌
#include <Wire.h> //I2C 통신 라이브러리
#include <LiquidCrystal_I2C.h> // LCD 사용 위한 라이브러리
#define BUTTON1 10
#define BUTTON2 9
#define BUTTON_START 8

/*
  I2C LCD는 SCL과 SDA 핀, VCC, GND 핀을 연결하여 사용한다.
  SCL핀은 아두이노의 A5 핀, SDA핀은 아두이노의 A4 핀과 연결한다.
  이는 I2C 통신에서 정해져있는 핀이므로 변경이 불가능하다.
*/

LiquidCrystal_I2C lcd(0x27,20,4);  // set the LCD address to 0x27 for a 16 chars and 2 line display

// 각 스위치별 클릭 횟수 저장 변수
unsigned int buttonCnt1 = 0;
unsigned int buttonCnt2 = 0;

// 경과 시간 계산 위한 변수
unsigned long currTime = 0;
unsigned long prevTime = 0;

// 전체 게임 시간
unsigned int gameTime = 30;

void setup()
{
  pinMode(BUTTON1, INPUT_PULLUP);
  pinMode(BUTTON2, INPUT_PULLUP);
  // 게임 시작 여부 전달 스위치
  pinMode(BUTTON_START, INPUT_PULLUP);
  lcd.init();                      // initialize the lcd 
  lcd.backlight();
}


void loop()
{
  // 첫번째 플레이어가 클릭한 경우
  if (button1P() == 1){
    // 게임 시간이 다 지나가지 않았으면 첫번째 플레이어의 클릭 횟수 1 증가
    if (gameTime > 0){
      buttonCnt1++;
    }
    delay(50);
  }
  // 두번째 플레이어가 클릭한 경우
  if (button2P() == 1){
    // 게임 시간이 다 지나가지 않았으면 두번째 플레이어의 클릭 횟수 1 증가
    if (gameTime > 0){
      buttonCnt2++;
    }
    delay(50);
  }
  // 게임이 시작된 경우
  if (buttonStart() == 1){
    // 전체 게임시간 30초로 설정, 각 플레이어의 클릭 횟수 0으로 설정
    gameTime = 30;
    buttonCnt1 = 0;
    buttonCnt2 = 0;
    delay(50);
  }

  // get the current time
  currTime = millis();
  // 현재 시간이 이전 시간보다 1초 이상 지나간 경우
  if(currTime - prevTime >= 1000){
    // 이전 시간을 현재 시간으로 갱신
    prevTime = currTime;
    // 게임 시간이 아직 다 지나가지 않은 경우 1초 감소
    // 플레이어가 현재 게임 시간이 얼마나 남았는지 확인 가능
    if (gameTime > 0){
      gameTime--;
    }
    // LCD 모든 글자 지움
    lcd.clear();
    // move cursor to 1 칸, 0줄(first line)
    lcd.setCursor(3,0);
    lcd.print("Time : ");
    lcd.print(gameTime);
    // move cursor to 5 칸, 1줄(second line)
    lcd.setCursor(0,1);
    lcd.print("1P : ");
    lcd.print(buttonCnt1);
    // move cursor to 8 칸, 1줄(second line)
    lcd.setCursor(8,1);
    lcd.print("2P : ");
    lcd.print(buttonCnt2);
  }
}

// 첫번째 플레이어의 스위치 클릭 여부를 반환하는 함수
int button1P(){
  // 정적 변수 선언 - 함수 호출 시 이전에 설정한 값을 그대로 유지하기 위함
  static int oldSW = 1;
  static int newSW = 1;
  newSW = digitalRead(BUTTON1);
  // 클릭한 경우 - 이전값과 현재값이 서로 다른 경우
  if (newSW != oldSW){
    oldSW = newSW;
    // 새로운 값이 1 -> 0으로 변화한 경우 클릭이 이루어졌으므로 1 반환
    if (newSW == 0){
      return 1;
    }
  }
  // 클릭하지 않았으면 0 반환
  return 0;
}

// 두번째 플레이어의 스위치 클릭 여부를 반환하는 함수
int button2P(){
  static int oldSW = 1;
  static int newSW = 1;
  newSW = digitalRead(BUTTON2);
  if (newSW != oldSW){
    oldSW = newSW;
    if (newSW == 0){
      return 1;
    }
  }
  return 0;
}

// 게임의 시작을 알려주는 스위치의 클릭 여부를 반환하는 함수
int buttonStart(){
  static int oldSW = 1;
  static int newSW = 1;
  newSW = digitalRead(BUTTON_START);
  if (newSW != oldSW){
    oldSW = newSW;
    if (newSW == 0){
      return 1;
    }
  }
  return 0;
}
/*
i2c_scanner : I2C LCD 모니터의 주소를 알아내는 코드
보통 0x27이 많지만 가끔 0x3F가 나오는 경우가 있어 확인 필요

 // --------------------------------------
// i2c_scanner
//
// Version 1
//    This program (or code that looks like it)
//    can be found in many places.
//    For example on the Arduino.cc forum.
//    The original author is not know.
// Version 2, Juni 2012, Using Arduino 1.0.1
//     Adapted to be as simple as possible by Arduino.cc user Krodal
// Version 3, Feb 26  2013
//    V3 by louarnold
// Version 4, March 3, 2013, Using Arduino 1.0.3
//    by Arduino.cc user Krodal.
//    Changes by louarnold removed.
//    Scanning addresses changed from 0...127 to 1...119,
//    according to the i2c scanner by Nick Gammon
//    https://www.gammon.com.au/forum/?id=10896
// Version 5, March 28, 2013
//    As version 4, but address scans now to 127.
//    A sensor seems to use address 120.
// Version 6, November 27, 2015.
//    Added waiting for the Leonardo serial communication.
// 
//
// This sketch tests the standard 7-bit addresses
// Devices with higher bit address might not be seen properly.
//

#include <Wire.h>


void setup()
{
  Wire.begin();

  Serial.begin(9600);
  while (!Serial);             // Leonardo: wait for serial monitor
  Serial.println("\nI2C Scanner");
}


void loop()
{
  byte error, address;
  int nDevices;

  Serial.println("Scanning...");

  nDevices = 0;
  for(address = 1; address < 127; address++ ) 
  {
    // The i2c_scanner uses the return value of
    // the Write.endTransmisstion to see if
    // a device did acknowledge to the address.
    Wire.beginTransmission(address);
    error = Wire.endTransmission();

    if (error == 0)
    {
      Serial.print("I2C device found at address 0x");
      if (address<16) 
        Serial.print("0");
      Serial.print(address,HEX);
      Serial.println("  !");

      nDevices++;
    }
    else if (error==4) 
    {
      Serial.print("Unknown error at address 0x");
      if (address<16) 
        Serial.print("0");
      Serial.println(address,HEX);
    }    
  }
  if (nDevices == 0)
    Serial.println("No I2C devices found\n");
  else
    Serial.println("done\n");

  delay(5000);           // wait 5 seconds for next scan
}
*/
