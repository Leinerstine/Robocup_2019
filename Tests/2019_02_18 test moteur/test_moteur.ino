#include "Grove_I2C_Motor_Driver.h"

#define I2C_ADDRESS_D 0x0a
#define I2C_ADDRESS_G 0x0f

//la vitesse varie entre -100 et 100, en négatif = sens contraire des aiguilles d'une montre
//MOTOR1 = roue avant

char vitesse = 70; 
int motor;
int motor;

void setup() {
  motor = Motor.begin(I2C_ADDRESS_D);
  motor = Motor.begin(I2C_ADDRESS_G);
}

void loop() {
    avancer(vitesse);
    delay(2000);
}

void avancer(char vitesse)
{
    Motor.speed(MOTOR1, vitesse);
    Motor.speed(MOTOR2, vitesse);
}