void setup(){
  Serial.begin(9600);
}

void loop(){
  Serial.println("hello from arduino");
  Serial.println(123);
  
  if(Serial.available()){
    int a = Serial.read();
    Serial.print(a);
    Serial.println(" is received");
  }
  
  delay(1000);
}
