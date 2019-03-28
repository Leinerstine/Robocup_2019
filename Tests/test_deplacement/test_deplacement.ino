#include "MoveMotor.h"
#include "Gyroscope.h"
#include "Ultrason.h"
#include "Button.h"
#include "Temperature.h"

#define DELTA_TIME 5000

void mfw_analyze(int *PneedMove);

//initialise les differents elements
Gyroscope g_Gyroscope;
Robot_Move g_Motor; 
Ultrason g_Ultrason;
Button g_MainButton(8);
Temperature g_Temp;

//variable et pointeur stockant la demande de mouvement
int needMove = 1;
int *PneedMove = &needMove;
bool g_bStop = true; //stock la demande d'arret 
bool g_bDebugMode = true;
long Time = 0;

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

  if (g_MainButton.IsLongReleased())
  {
      if (g_bDebugMode)
      {
        g_bDebugMode = false;
        g_Temp.StopDebug();
      }
      else
      {
        g_bDebugMode = true;
      }
  }
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


    if (g_MainButton.IsShortReleased()) {
        g_bStop = !g_bStop;
    }

    if (g_bStop) {
        g_Motor.ChangeOrder(Robot_Move::STAY, 0, 0);
    }
    else
    {
        if (*PneedMove = 1) {
        *PneedMove = 0;
        mfw_analyze(PneedMove);
        }   
    }
} 

void mfw_analyze(int *PneedMove)
{
    int i = 0; //variable de boucle

    int r_distance, bw_distance, l_distance, fw_distance = 0; //variable stockant la distance entre le mur et le robot
    
    //AVANCE
    g_Motor.ChangeOrder(Robot_Move::FORWARD, 3000, 0); //avancer 3s
    Serial.print("avance\n");
    //delay(5000);
    if(Time > millis())
      return;
    Time = millis() + DELTA_TIME;
    
    //ANALYSE AUTOUR DE LUI
    for(i = 0; i<4; i++)
    {
        g_Motor.ChangeOrder(Robot_Move::RIGHT, 0, 90); //tourner 90°
        Serial.print("droite\n");
        //delay(5000);
        if(Time > millis())
          return;
        Time = millis() + DELTA_TIME;
        g_Ultrason.Update();
        //analyse la distance 
        switch (i)
        {
            case 0 :
                r_distance = g_Ultrason.GetDistance();
                Serial.print("obstacle a droite a : ");
                Serial.print(r_distance);
                Serial.print("\n");
                break;
            case 1 :
                bw_distance = g_Ultrason.GetDistance();
                Serial.print("obstacle derriere a : ");
                Serial.print(bw_distance);
                Serial.print("\n");
                break;
            case 2 :
                l_distance = g_Ultrason.GetDistance();
                Serial.print("obstacle a gauche a : ");
                Serial.print(l_distance);
                Serial.print("\n");
                break;
            case 3 :
                fw_distance = g_Ultrason.GetDistance();
                Serial.print("obstacle en face a : ");
                Serial.print(fw_distance);
                Serial.print("\n");
                break;
        }
        
        //analyse infrarouge + distribution medikit
    }

    //CHOISIS LA FUTURE DIRECTION 
    if (r_distance < 10) {
        if (fw_distance < 10) {
            if (l_distance < 10) {
                g_Motor.ChangeOrder(Robot_Move::LEFT, 0, 180); //tourner 90°
                Serial.print("demi-tour\n");
                //delay(5000);
                if(Time > millis())
                  return;
                Time = millis() + DELTA_TIME;
                *PneedMove = 1;
            }
            else {
                g_Motor.ChangeOrder(Robot_Move::LEFT, 0, 90); //tourner 90°
                Serial.print("gauche\n");
                //delay(5000);
                if(Time > millis())
                  return;
                Time = millis() + DELTA_TIME;
                *PneedMove = 1;
            }
            
        }
        else {
            *PneedMove = 1;
        }
        
    }
    
    else {
        g_Motor.ChangeOrder(Robot_Move::RIGHT, 0, 90); //tourner 90°
        Serial.print("droite\n");
        //delay(5000);
        if(Time > millis())
          return;
        Time = millis() + DELTA_TIME;
        *PneedMove = 1;
    }
    
}