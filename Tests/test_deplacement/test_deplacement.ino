#include "tools\Button.h"
#include "tools\MoveMotor.h"
#include "tools\Gyroscope.h"
#include "tools\Ultrason.h"
#include "tools\Temperature.h"

Gyroscope g_gyroscope; //je déclare mes variables liées aux .h
bool g_bDebugMode = true;
Robot_Move g_Motor; 
bool  g_bStop = true; //au départ le robot est à l'arrêt
Button g_MainButton(8); //le bouton pressoir est au port D8
Ultrason g_Ultrason;
Temperature g_Temp;

int g_IntCurrentOrder=0; //actuellement STAY


void setup() 
{
  g_Motor.Setup(); //moteurs
  g_Temp.Setup();
  g_gyroscope.Setup();
  Serial.begin(9600);

}

void loop() 
{

  g_gyroscope.Update();
  g_Motor.Update(g_gyroscope.GetRawAngle());
  g_MainButton.Update(); 
  g_Ultrason.Update();
  g_Temp.Update();

 if (g_bDebugMode)
 {
    char txt1[256];
    char txt2[256];
    char txt3[256];
    long t = g_Temp.GetTemperature();
    long d = g_Ultrason.GetDistance();
    long a = g_gyroscope.GetRawAngle();

    sprintf(txt1, "T %d",t);// D %d A %d", t, d, a);
    sprintf(txt2, " D %d",d);// D %d A %d", t, d, a);
    sprintf(txt3, " A %d   ",a);// D %d A %d", t, d, a);
    strcat(txt1, txt2); //on met txt 2 dans txt1
    strcat(txt1, txt3); //txt3 dans txt1
    g_Temp.DrawDebug(txt1);
 }


  if (g_MainButton.IsReleased())
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