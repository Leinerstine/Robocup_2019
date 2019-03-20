#include "MoveMotor.h"
#include "Gyroscope.h"
#include "Ultrason.h"

Gyroscope g_Gyroscope;
Robot_Move g_Motor;
Ultrason g_Ultrason;

int d = 0;

void setup()
{
 g_Motor.Setup();
 g_Gyroscope.setup();
 Serial.begin(9600);
}

void loop()
{
  g_Gyroscope.Update();
  g_Motor.Update(g_Gyroscope.GetRawAngle());
  g_Ultrason.Update();
  
  g_Motor.ChangeOrder(Robot_Move::STAY, 0, 0);
  g_Motor.ChangeOrder(Robot_Move::FORWARD, 1000,0);
  delay(1000);
  
  d = g_Ultrason.GetDistance();
  Serial.print(d);
 }