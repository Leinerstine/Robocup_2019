#include "Button.h"
#include "MoveMotor.h"
#include "Gyroscope.h"

Gyroscope g_gyroscope;
Robot_Move g_Motor; 
bool  g_bStop = true;
Button g_MainButton(8);

int g_IntCurrentOrder=0;


void setup() 
{
  g_Motor.Setup();
  Serial.begin(9600);
  g_gyroscope.setup();
  
}

void loop() 
{

  g_gyroscope.Update();
  g_Motor.Update(g_gyroscope.GetRawAngle());
  g_MainButton.Update(); 


  if (g_MainButton.IsPressed())
    g_bStop = !g_bStop;

  if(g_bStop)
  {
    g_IntCurrentOrder = 0;
    g_Motor.ChangeOrder(Robot_Move::STAY, 0, 0);
    delay(100);
    return;
  }
  
  Serial.println(g_gyroscope.GetRawAngle());
  
  if (g_Motor.GetOrder() == Robot_Move::STAY)
  {
    
    if (g_IntCurrentOrder==0) //compteur ordre actuel
      g_Motor.ChangeOrder(Robot_Move::FORWARD, 2000, 0); //avance 2 secondes puis repasse en STAY
    else if (g_IntCurrentOrder==1)
      g_Motor.ChangeOrder(Robot_Move::LEFT_ANGLE, 0, 85); //angle 90
      
    
    g_IntCurrentOrder++;
    if (g_IntCurrentOrder==2)
      g_IntCurrentOrder = 0;    
  }
}