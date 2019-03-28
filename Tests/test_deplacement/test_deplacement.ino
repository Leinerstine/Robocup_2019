#include "Button.h"
#include "MoveMotor.h"
#include "Gyroscope.h"
#include "Ultrason.h"

//initialise les differents elements
Gyroscope g_Gyroscope;
Robot_Move g_Motor; 
Ultrason g_Ultrason;
Button g_MainButton(2);

//variable et pointeur stockant la demande de mouvement
int needMove = 1;
int *PneedMove = &needMove;
bool g_bStop = true; //stock la demande d'arret 

void setup() 
{
//lance le moteur, gyroscope et moniteur
    g_Motor.Setup();
    g_Gyroscope.setup();
    Serial.begin(9600);
}

void loop()
{
    g_Gyroscope.Update();
    g_Motor.Update(g_Gyroscope.GetRawAngle());
    g_MainButton.Update();

    if (g_MainButton.IsPressed()) {
        g_bStop = !g_bStop;
    }

    if (g_bStop) {
        g_Motor.ChangeOrder(Robot_Move::STAY, 0, 90);
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
    delay(5000);
    
    //ANALYSE AUTOUR DE LUI
    for(i = 0; i<4; i++)
    {
        g_Motor.ChangeOrder(Robot_Move::RIGHT, 0, 90); //tourner 90°
        Serial.print("droite\n");
        delay(5000);
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
                delay(5000);
                *PneedMove = 1;
            }
            else {
                g_Motor.ChangeOrder(Robot_Move::LEFT, 0, 90); //tourner 90°
                Serial.print("gauche\n");
                delay(5000);
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
        delay(5000);
        *PneedMove = 1;
    }
}