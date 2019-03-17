#ifndef _GYRO_SENSOR_
#define _GYRO_SENSOR_
#include "\librairies\Accelerometer_And_Gyroscope_LSM6DS3-masterAccelerometer_And_Gyroscope_LSM6DS3-master\SparkFunLSM6DS3.h"

class Gyroscope
{
    LSM6DS3 myIMU; //premiere phase initialisation
    float m_z; //position dans l'espace (angle sur droite gauche)
    unsigned long m_time; //temps

    public:
    Gyroscope() : myIMU(I2C_MODE, 0x6A) //iniialisation du Gyroscope (adresse)
    {
        m_z = 0; //initialisation temps 
        m_time = micros(); //temps en microsecondes
    }

    float   GetRawAngle() const
    {
      return m_z; //on reçoit l'angle 
    }

    void setup()
    {
      myIMU.begin(); //on commence
      
    }

    void    Update()
    {
      unsigned long newTime = micros(); //nouveau temps
      float fDeltaTimeMicros = (newTime - m_time); //Nouveau temps moins l'ancien : période

      m_time = newTime; //l'ancien temps devient le nouveau : permettre prochain calcul période 

      float fSpeedAngle = myIMU.readFloatGyroZ(); //on lit l'angle Z
      if (fabs(fSpeedAngle)<0.5f) //si la difference est tres faible alors ça ne vaut pas la peine -> réduire erreur
        fSpeedAngle = 0.f;
      
      float fDeltaAngle = (fSpeedAngle * fDeltaTimeMicros) * (1.f / 1000000.f); // on fait distance / temps * 1 microsecondes
      m_z = m_z + fDeltaAngle; //angle actuel 
    }
    
};


#endif
