#include "main.h"
#define led LED_BUILTIN


void setup_led() {
  pinMode(led, OUTPUT);
}

void loop_led() {
  digitalWrite(led, HIGH);
  delay(1000);
  digitalWrite(led, LOW);
  delay(2000);
}