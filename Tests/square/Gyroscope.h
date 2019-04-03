#ifndef _GYRO_SENSOR_
#define _GYRO_SENSOR_
#include "SparkFunLSM6DS3.h"

class Gyroscope
{
    LSM6DS3 myIMU;
    float m_z;
    unsigned long m_time; 

    public:
    Gyroscope() : myIMU(I2C_MODE, 0x6A)
    {
        m_z = 0;
        m_time = micros();
    }

    float   GetRawAngle() const
    {
      return m_z;
    }

    void Setup()
    {
      myIMU.begin();
      
    }

    void    Update()
    {
      unsigned long newTime = micros();
      float fDeltaTimeMicros = (newTime - m_time);
     // if (fDeltaTimeMicros < 1000.f)
       // return; // n update pas trop souvent
      m_time = newTime;

      float fSpeedAngle = myIMU.readFloatGyroZ();
      //if (fabs(fSpeedAngle)<0.5f)
        //fSpeedAngle = 0.f;
      
      float fDeltaAngle = (fSpeedAngle * fDeltaTimeMicros) * (1.f / 1000000.f);
      m_z = m_z + fDeltaAngle;
    }
    
};


#endif
