#include "tools\Button.h"
#include "tools\MoveMotor.h"
#include "tools\Gyroscope.h"
#include "tools\Ultrason.h"

Gyroscope g_gyroscope; //je déclare mes variables liées aux .h
Robot_Move g_Motor; 
bool  g_bStop = true; //au départ le robot est à l'arrêt
Button g_MainButton(2); //le bouton pressoir est au port D2
Ultrason g_Ultrason;

int g_IntCurrentOrder=0; //actuellement STAY


void setup() 
{
  g_Motor.Setup(); //moteurs
  Serial.begin(9600);

}

void loop() 
{

  g_gyroscope.Update();
  g_Motor.Update(g_gyroscope.GetRawAngle());
  g_MainButton.Update(); 
  g_Ultrason.Update();
  Serial.print(g_Ultrason.GetDistance());


  if (g_MainButton.IsPressed())
    g_bStop = !g_bStop;

  if(g_bStop)
  {
    g_IntCurrentOrder = 0;
    g_Motor.ChangeOrder(Robot_Move::STAY, 0, 0);
    delay(100);
    return;
  }

   
  if (g_Motor.GetOrder() == Robot_Move::STAY)
  {
    
    if (g_IntCurrentOrder==0) //compteur ordre actuel
      g_Motor.ChangeOrder(Robot_Move::FORWARD, 2000, 0); //avance 2 secondes puis repasse en STAY
    else if (g_IntCurrentOrder==1)
      g_Motor.ChangeOrder(Robot_Move::LEFT_ANGLE, 0, 90); //angle 90
      else if (g_IntCurrentOrder==2)
      g_Motor.ChangeOrder(Robot_Move::RIGHT_ANGLE, 0, 180);

    g_IntCurrentOrder++;
    if (g_IntCurrentOrder==3)
      g_IntCurrentOrder = 0;
 
    
  }
}
