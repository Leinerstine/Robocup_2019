#ifndef _GYRO_SENSOR_
#define _GYRO_SENSOR_
#include "SparkFunLSM6DS3.h"

class Gyroscope
{
    LSM6DS3 myIMU; //création du capteur 
    float m_z; //orientation (sur l'axe z, quand le robot est au sol pour l'angle)
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

    void Setup()
    {
      myIMU.begin(); //nécessaire pour commencer
    }

    void Update()
    {
      unsigned long newTime = micros(); //on prend le temps actuel 
      float fDeltaTimeMicros = (newTime - m_time); //différence de temps avec la dernière actualisation
      if (fDeltaTimeMicros < 1000.f)
        return; // n update pas trop souvent
      m_time = newTime;

      float fSpeedAngle = myIMU.readFloatGyroZ(); //lit valeur angle Z 
      if (fabs(fSpeedAngle)<5.f) //valeur absolue inférieure à 5° (manque de précision du capteur)
        fSpeedAngle = 0.f; //pas de variation 
      
      float fDeltaAngle = (fSpeedAngle * fDeltaTimeMicros) * (1.f / 1000000.f); //angle*temps / 1 micros
      m_z = m_z + fDeltaAngle; //orientation actuel = angle précédent + changement d'angle 
    }
};


#endif
