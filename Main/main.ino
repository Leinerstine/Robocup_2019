//#include "main.h"
#define led LED_BUILTIN
void loop_led();
void setup_led();

void setup()
{
  setup_led();
}

void loop()
{
  loop_led();
}


void setup_led() {
  pinMode(led, OUTPUT);
}

void loop_led() {
  digitalWrite(led, HIGH);
  delay(1000);
  digitalWrite(led, LOW);
  delay(1000);
}