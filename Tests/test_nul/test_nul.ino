#include "tools\Button.h"                                                                   
#include "tools\MoveMotor.h"
#include "tools\Gyroscope.h"
#include "tools\Ultrason.h"
#include "tools\Button.h"
#include "tools\Temperature.h"                

#define DELTA_TIME 5000

//initialise les differents elements
Gyroscope g_Gyroscope;
Robot_Move g_Motor; 
Ultrason g_Ultrason;
Button g_MainButton(8);
Temperature g_Temp;

//variable et pointeur stockant la demande de mouvement
int   g_CurrentOrder = 0;
bool  g_bStop = true; //stock la demande d'arret 
bool  g_bDebugMode = true;
long  Time = millis();

void setup() 
{
//lance le moteur, gyroscope et moniteur
    g_Motor.Setup();
    g_Gyroscope.Setup();
    g_Temp.Setup();
    Serial.begin(9600);
}

void loop()
{
    g_Gyroscope.Update();
    g_Motor.Update(g_Gyroscope.GetRawAngle());
    g_MainButton.Update();
    g_Ultrason.Update();
    g_Temp.Update();
    unsigned long NewTime = millis();

  if (g_bDebugMode)
  {
      char txt1[256];
      char txt2[256];
      char txt3[256];
      long t = g_Temp.GetTemperature();
      long d = g_Ultrason.GetDistance();
      long a = g_Gyroscope.GetRawAngle();

      sprintf(txt1, "T %d",t);// D %d A %d", t, d, a);
      sprintf(txt2, " D %d",d);// D %d A %d", t, d, a);
      sprintf(txt3, " A %d   ",a);// D %d A %d", t, d, a);
      strcat(txt1, txt2);
      strcat(txt1, txt3);
      g_Temp.DrawDebug(txt1);
  }


    if (g_MainButton.IsPressed()) {
        g_bStop = !g_bStop;
    }

    if (g_bStop) 
    {
        g_CurrentOrder = 0;
        g_Motor.ChangeOrder(Robot_Move::STAY, 0, 0);
        return;
    }
    
    Serial.print("Je démarre.\n");

    if(Time < NewTime + DELTA_TIME)
    {
      switch(g_CurrentOrder)
      {
        case 0:
          g_Motor.ChangeOrder(Robot_Move::FORWARD, 2000, 0);
          break;
        case 4:
        case 3:
        case 2:
        case 1:
          g_Motor.ChangeOrder(Robot_Move::LEFT_ANGLE,0,85);
          break;
      }
    }
    else 
    {
      g_CurrentOrder = 0;
      Time = NewTime;
    }
} 
