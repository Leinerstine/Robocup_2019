#ifndef _ULTRASON_
#define _ULTRASON_
#include "librairies\Grove_Ultrasonic_Ranger-master\Ultrasonic.h" 


class Ultrason 
{
    long m_distance;
    unsigned long m_time;

    public:
    Ultrason() 
    {
        m_distance = 0; //distance
        m_time = millis();
    }

    Ultrasonic.ultrasonic(12);

    long GetDistance() const 
    {
        return m_distance; 
    }

    void Update()
    {
        unsigned long NewTime = micros();
        while(NewTime - m_time < 100);
        m_distance = ultrasonic.MeasureInCentimeters();
        m_time = NewTime;
    }
};


#endif