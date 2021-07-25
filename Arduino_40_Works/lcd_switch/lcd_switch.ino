// 스위치를 30초 동안 많이 누르기 게임
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#define BUTTON1 10
#define BUTTON2 9
#define BUTTON_START 8

LiquidCrystal_I2C lcd(0x27,20,4);  // set the LCD address to 0x27 for a 16 chars and 2 line display

unsigned int buttonCnt1 = 0;
unsigned int buttonCnt2 = 0;

unsigned long currTime = 0;
unsigned long prevTime = 0;

unsigned int gameTime = 30;

void setup()
{
  pinMode(BUTTON1, INPUT_PULLUP);
  pinMode(BUTTON2, INPUT_PULLUP);
  pinMode(BUTTON_START, INPUT_PULLUP);
  lcd.init();                      // initialize the lcd 
  lcd.backlight();
}


void loop()
{
  if (button1P() == 1){
    if (gameTime > 0){
      buttonCnt1++;
    }
    delay(50);
  }
  if (button2P() == 1){
    if (gameTime > 0){
      buttonCnt2++;
    }
    delay(50);
  }
  if (buttonStart() == 1){
    gameTime = 30;
    buttonCnt1 = 0;
    buttonCnt2 = 0;
    delay(50);
  }

  currTime = millis();             // get the current time
  if(currTime - prevTime >= 1000){
    prevTime = currTime;
    if (gameTime > 0){
      gameTime--;
    }
    lcd.clear();
    lcd.setCursor(3,0);              // move cursor to 1 칸, 0줄(first line)
    lcd.print("Time : ");
    lcd.print(gameTime);
    lcd.setCursor(0,1);              // move cursor to 5 칸, 1줄(second line)
    lcd.print("1P : ");
    lcd.print(buttonCnt1);
    lcd.setCursor(8,1);              // move cursor to 5 칸, 1줄(second line)
    lcd.print("2P : ");
    lcd.print(buttonCnt2);
  }
}

int button1P(){
  static int oldSW = 1;
  static int newSW = 1;
  newSW = digitalRead(BUTTON1);
  if (newSW != oldSW){
    oldSW = newSW;
    if (newSW == 0){
      return 1;
    }
  }
  return 0;
}
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
