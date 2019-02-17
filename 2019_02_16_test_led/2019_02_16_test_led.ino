#define led LED_BUILTIN


void setup() {
  pinMode(led, OUTPUT);
}

void loop() {
  digitalWrite(led, HIGH);
  delay(560);
  digitalWrite(led, LOW);
  delay(200);
}