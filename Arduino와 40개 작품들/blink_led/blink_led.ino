#define LED1 10
#define LED2 8
#define DELAY_TIME 200

void setup() {
  // put your setup code here, to run once:
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(LED1, LOW);
  digitalWrite(LED2, HIGH);
  delay(DELAY_TIME);
  digitalWrite(LED1, HIGH);
  digitalWrite(LED2, LOW);
  delay(DELAY_TIME);
}
