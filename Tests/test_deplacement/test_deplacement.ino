#include "MoveMotor.h"
#include "Ultrason.h"

Robot_Move g_Motor; 

//variable et pointeur stockant la demande de mouvement
int needMove = 1;
int *PneedMove = &needMove;

void setup() 
{
    g_Motor.Setup();
    Serial.begin(9600);
}

void loop()
{
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
    int i = 0; //variable de boucle

    int r_distance, bw_distance, l_distance, fw_distance = 0; //variable stockant la distance entre le mur et le robot
    
    //AVANCE
    g_Motor.ChangeOrder(Robot_Move::FORWARD, 3000, 0); //avancer 3s

    //ANALYSE AUTOUR DE LUI
    for(i = 0; i<4; i++)
    {
        g_Motor.ChangeOrder(Robot_Move::RIGHT, 0, 90); //tourner 90°
        
        //analyse la distance 
        switch (i)
        {
            case 0 :
                r = GetDistance();
                break;
            case 1 :
                bw_distance = GetDistance();
                break;
            case 2 :
                l_distance = GetDistance();
                break;
            case 3 :
                fw_distance = GetDistance(); 
        }
        
        //analyse infrarouge + distribution medikit
    }

    //CHOISIS LA FUTURE DIRECTION 
    if (r_distance < 10) {
        if (fw_distance < 10) {
            if (l_distance < 10) {
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