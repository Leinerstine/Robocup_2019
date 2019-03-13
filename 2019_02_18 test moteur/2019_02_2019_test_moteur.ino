#include "Grove_I2C_Motor_Driver.h"
#define I2C_ADDRESS 0x0f

//la vitesse varie entre -100 et 100, en négatif = sens contraire des aiguilles d'une montre
//MOTOR1 = roue avant

void setup() {
  Motor.begin(I2C_ADDRESS);
}

void loop() {
  Motor.speed(MOTOR1, 50);
  //Motor.speed(MOTOR2, -70);
  delay(2000);
  Motor.speed(MOTOR1, -100);
  //Motor.speed(MOTOR2, 100);
  delay(2000);
  // Stop MOTOR1 and MOTOR2
  Motor.stop(MOTOR1);
  //Motor.stop(MOTOR2);
  delay(2000);
}
