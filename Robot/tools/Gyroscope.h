#ifndef _GYRO_SENSOR_
#define _GYRO_SENSOR_
#include "SparkFunLSM6DS3.h"

class Gyroscope
{
    LSM6DS3 myIMU; //création du capteur 
    float m_z; //orientation (sur l'axe z, quand le robot est au sol)
    unsigned long m_time; //temps

    public:
    Gyroscope() : myIMU(I2C_MODE, 0x6A) //paramètres par défaut, adresse du capteur
    {
        m_z = 0; //initialisation de départ pour l'orientation
        m_time = micros(); //temps en microsecondes (millisecondes pas assez précis)
    }

    float   GetRawAngle() const
    {
      return m_z; //on retourne l'angle
    }

    void setup()
    {
      myIMU.begin(); //nécessaire pour commencer
      
    }

    void    Update()
    {
      unsigned long newTime = micros();
      float fDeltaTimeMicros = (newTime - m_time); //différence de temps
      if (fDeltaTimeMicros < 1000.f)
        return; // n update pas trop souvent
      m_time = newTime;

      float fSpeedAngle = myIMU.readFloatGyroZ();
      if (fabs(fSpeedAngle)<0.5f)
        fSpeedAngle = 0.f;
      
      float fDeltaAngle = (fSpeedAngle * fDeltaTimeMicros) * (1.f / 1000000.f);
      m_z = m_z + fDeltaAngle;
    }
    
};


#endif
