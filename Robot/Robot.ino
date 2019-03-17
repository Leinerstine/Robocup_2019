#include "Button.h"
#include "MoveMotor.h"

Robot_Move g_Motor; 
bool  g_bStop = true;
Button g_MainButton(2);

int g_IntCurrentOrder=0;


void setup() 
{
  g_Motor.Setup();
  Serial.begin(9600);

}

void loop() 
{


  g_Motor.Update();
  g_MainButton.Update(); 

  if (g_MainButton.IsPressed())
    g_bStop = !g_bStop;

  if(g_bStop)
  {
    g_IntCurrentOrder = 0;
    g_Motor.ChangeOrder(Robot_Move::STAY, 0);
    return;
  }

   //g_Motor.ChangeOrder(Robot_Move::LEFT, 0);
   //return;

  //Serial.print(g_Motor.GetOrder());
  if (g_Motor.GetOrder() == Robot_Move::STAY)
  {
    if (g_IntCurrentOrder==0)
      g_Motor.ChangeOrder(Robot_Move::FORWARD, 2000);
    else if (g_IntCurrentOrder==1)
      g_Motor.ChangeOrder(Robot_Move::LEFT, 500);

    g_IntCurrentOrder++;
    if (g_IntCurrentOrder==2)
      g_IntCurrentOrder = 0;
 
    
  }
}
