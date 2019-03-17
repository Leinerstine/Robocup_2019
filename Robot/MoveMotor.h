#ifndef _MOVEMOTOR_
#define _MOVEMOTOR_ 


#include "Grove_I2C_Motor_Driver.h"
#define I2C_ADDRESS 0x0f
#define I2C_TWO 0x0a

class Robot_Move
{
    public:
    enum CurrentOrder
    {
        STAY,
        FORWARD,
        BACKWARD,
        LEFT,
        RIGHT,
        LEFT_ANGLE,
        RIGHT_ANGLE        
    };

    private:
    I2CMotorDriver m_motor1;
    I2CMotorDriver m_motor2;
    CurrentOrder    m_CurrentOrder;
    unsigned long   m_EndTimeOrder;
    float           m_fFinalAngle;
    float           m_fCurrentAngle;


    public:
    Robot_Move()
    {
        m_CurrentOrder = STAY;
        m_EndTimeOrder = 0xFFFFFFFF;
        m_fFinalAngle = 0.f;
        m_fCurrentAngle = 0.f;
    }

    void    Setup()
    {
        m_motor1.begin(I2C_ADDRESS);
        m_motor2.begin(I2C_TWO);
    }


    CurrentOrder  GetOrder() const 
    {
      return m_CurrentOrder;
    }

    void    ChangeOrder(CurrentOrder _order, unsigned long _Timems, float _fDeltaAngle)
    {
        m_EndTimeOrder = millis() + _Timems;
        if (_Timems==0)
           m_EndTimeOrder = 0xFFFFFFFF;

        if (_order == RIGHT_ANGLE)
        {
          m_fFinalAngle = m_fCurrentAngle +fabs(_fDeltaAngle);
          m_EndTimeOrder = 0xFFFFFFFF;
        }
        else if (_order == LEFT_ANGLE)
        {
          m_fFinalAngle = m_fCurrentAngle -fabs(_fDeltaAngle);       
          m_EndTimeOrder = 0xFFFFFFFF;   
        }

        m_CurrentOrder = _order;
 
    }
    void    Update(float _currentAngle)
    {
  
       m_fCurrentAngle = _currentAngle;
        if (millis()>m_EndTimeOrder)
            ChangeOrder(STAY, 0, 0);

        const int vitesse = 100;

        switch(m_CurrentOrder)
        {
            case STAY:
                m_motor1.stop(MOTOR1);
                m_motor1.stop(MOTOR2);
                m_motor2.stop(MOTOR1);
                m_motor2.stop(MOTOR2);
                break;
            case FORWARD:
                m_motor1.speed(MOTOR1, -vitesse);
                m_motor1.speed(MOTOR2, vitesse);
                m_motor2.speed(MOTOR1, -vitesse);
                m_motor2.speed(MOTOR2, vitesse);
                break;
            case BACKWARD:
                m_motor1.speed(MOTOR1, vitesse);
                m_motor1.speed(MOTOR2, -vitesse);
                m_motor2.speed(MOTOR1, vitesse);
                m_motor2.speed(MOTOR2, -vitesse);
                break;
            case LEFT_ANGLE:  
            case LEFT:
                m_motor1.speed(MOTOR1, -vitesse);
                m_motor1.speed(MOTOR2, -vitesse);
                m_motor2.speed(MOTOR1, -vitesse);
                m_motor2.speed(MOTOR2, -vitesse);
                break;
            case RIGHT_ANGLE:      
            case RIGHT:
                m_motor1.speed(MOTOR1, vitesse);
                m_motor1.speed(MOTOR2, vitesse);
                m_motor2.speed(MOTOR1, vitesse);
                m_motor2.speed(MOTOR2, vitesse);
                break;
        }

        if (m_CurrentOrder == LEFT_ANGLE && _currentAngle <= m_fFinalAngle)
            ChangeOrder(STAY,0,0);  
        if (m_CurrentOrder == RIGHT_ANGLE && _currentAngle >= m_fFinalAngle)
            ChangeOrder(STAY,0,0);      
    }
};


#endif 
