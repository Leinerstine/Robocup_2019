#ifndef _MOVEMOTOR_
#define _MOVEMOTOR_ 


#include "Grove_I2C_Motor_Driver.h"
#define I2C_ADDRESS 0x0f //on définit les deux adresses des Motor Driver 
#define I2C_TWO 0x0a

class Robot_Move
{
    public:
    enum CurrentOrder //differents etats des moteurs
    {
        STAY,
        FORWARD,
        BACKWARD,
        LEFT,
        RIGHT,
        LEFT_ANGLE,
        RIGHT_ANGLE        
    };

    private: // m_ = membre
    I2CMotorDriver  m_motor1;
    I2CMotorDriver  m_motor2;
    CurrentOrder    m_CurrentOrder; //état actuel
    unsigned long   m_EndTimeOrder; //temps où finir action 
    float           m_fFinalAngle; //angle à obtenir
    float           m_fCurrentAngle; //angle actuel


    public:
    Robot_Move() //initialisation 
    {
        m_CurrentOrder = STAY;
        m_EndTimeOrder = 0xFFFFFFFF; //infini en hexadécimal 
        m_fFinalAngle = 0.f;
        m_fCurrentAngle = 0.f;
    }

    void    Setup()
    {
        m_motor1.begin(I2C_ADDRESS); //Les deux roues à droite
        m_motor2.begin(I2C_TWO); //Les deux roues à gauche
    }


    CurrentOrder  GetOrder() const //récupérer ordre actuel
    {
      return m_CurrentOrder; 
    }

    void    ChangeOrder(CurrentOrder _order, unsigned long _Timems, float _fDeltaAngle)
    {
        m_EndTimeOrder = millis() + _Timems; //temps en millisecondes actuel
        if (_Timems==0)
           m_EndTimeOrder = 0xFFFFFFFF;

        if (_order == RIGHT_ANGLE)
        {
          m_fFinalAngle = m_fCurrentAngle +fabs(_fDeltaAngle); //angle actuel + valeur absolue angle recherché
          m_EndTimeOrder = 0xFFFFFFFF;
        }
        else if (_order == LEFT_ANGLE)
        {
          m_fFinalAngle = m_fCurrentAngle -fabs(_fDeltaAngle); //angle actuel - valeur absolue angle recherché
          m_EndTimeOrder = 0xFFFFFFFF;   
        }

        m_CurrentOrder = _order;
 
    }
    void    Update(float _currentAngle) //mise à jour angle actuel 
    {
  
       m_fCurrentAngle = _currentAngle;
        if (millis()>m_EndTimeOrder) //temps en millisecondes supérieur temps final exécution 
            ChangeOrder(STAY, 0, 0); //STOP

        const int vitesse = 100;

        switch(m_CurrentOrder)
        {
            case STAY: //on ne bouge pas
                m_motor1.stop(MOTOR1);
                m_motor1.stop(MOTOR2);
                m_motor2.stop(MOTOR1);
                m_motor2.stop(MOTOR2);
                break;
            case FORWARD: //les deux moteurs en avant
                m_motor1.speed(MOTOR1, -vitesse);
                m_motor1.speed(MOTOR2, vitesse);
                m_motor2.speed(MOTOR1, -vitesse);
                m_motor2.speed(MOTOR2, vitesse);
                break;
            case BACKWARD: //les deux moteurs vers l'arrière
                m_motor1.speed(MOTOR1, vitesse);
                m_motor1.speed(MOTOR2, -vitesse);
                m_motor2.speed(MOTOR1, vitesse);
                m_motor2.speed(MOTOR2, -vitesse);
                break;
            case LEFT_ANGLE:  //si il faut tourner vers la gauche alors on continue sur case LEFT (absence de break)
            case LEFT:
                m_motor1.speed(MOTOR1, -vitesse);
                m_motor1.speed(MOTOR2, -vitesse);
                m_motor2.speed(MOTOR1, -vitesse);
                m_motor2.speed(MOTOR2, -vitesse);
                break;
            case RIGHT_ANGLE: //idem tourner vers la droite   
            case RIGHT:
                m_motor1.speed(MOTOR1, vitesse);
                m_motor1.speed(MOTOR2, vitesse);
                m_motor2.speed(MOTOR1, vitesse);
                m_motor2.speed(MOTOR2, vitesse);
                break;
        }

        if (m_CurrentOrder == LEFT_ANGLE && _currentAngle <= m_fFinalAngle) //si ordre actuel == tourner gauche et que l'angle final est supérieur à angle actuel 
            ChangeOrder(STAY,0,0);  
        if (m_CurrentOrder == RIGHT_ANGLE && _currentAngle >= m_fFinalAngle) //si ordre actuel == tourner droite et que l'angle final est supérieur à angle actuel 
            ChangeOrder(STAY,0,0);      
    }
};


#endif 
