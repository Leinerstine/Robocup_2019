#include "Button.h"
#include "MoveMotor.h"
#include "Gyroscope.h"

Gyroscope g_gyroscope;
Robot_Move g_Motor; 

int needMove = 1;
int *PneedMove = &needmove;

void setup() 
{
    g_Motor.Setup();
    Serial.begin(9600);
}

void loop()
{
    g_gyroscope.Update();
    g_Motor.Update(g_gyroscope.GetRawAngle());
    g_MainButton.Update();

    if (*PneedMove = 1) {
        *PneedMove = 0;
        mfw_analyze(PneedMove)
    }
    else if (*PneedMove != 1) {
        //ne rien faire 
    }
    
    

} 

void mfw_analyze(int *needMove)
{
    int i = 0;

    int r_distance, bw_distance, l_distance, fw_distance = 0;
    
    //AVANCE
    g_Motor.ChangeOrder(Robot_Move::FORWARD, 3000, 0); //avancer 3s

    //ANALYSE AUTOUR DE LUI
    for(i = 0; i<4; i++)
    {
        g_Motor.ChangeOrder(Robot_Move::RIGHT, 0, 90); //tourner 90°
        
        //analyse la distance 
        switch (i)
        {
            case : 0
                *r = //distance
                break;
            case : 1
                *bw_distance = //distance
                break;
            case : 2
                *l_distance = //distance
                break;
            case : 3
                *fw_distance = //distance 
        }
        
        //analyse infrarouge + distribution medikit
    }

    //CHOISIS LA FUTURE DIRECTION 
    if (*r < 10) {
        if (*fw < 10) {
            if (*l < 10) {
                g_Motor.ChangeOrder(Robot_Move::LEFT, 0, 180); //tourner 90°
                *PneedMove = 1;
            }
            else {
                g_Motor.ChangeOrder(Robot_Move::LEFT, 0, 90); //tourner 90°
                *PneedMove = 1;
            }
            
        }
        else {
            *PneedMove = 1;
        }
        
    }
    
    else {
        g_Motor.ChangeOrder(Robot_Move::RIGHT, 0, 90); //tourner 90°
        *PneedMove = 1;
    }
    
}