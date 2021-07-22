void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(8, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  if (Serial.available() > 0){
    char sData = Serial.read();
    if (sData == 'a'){
      digitalWrite(8, HIGH);
    }
    else if (sData == 'b'){
      digitalWrite(8, LOW);
    }
    else if (sData == 'c'){
      digitalWrite(8, HIGH);
      delay(1000);
      digitalWrite(8, LOW);
      delay(1000);
    }
  }
}
