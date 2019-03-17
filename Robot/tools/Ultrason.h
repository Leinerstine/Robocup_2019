#ifndef _ULTRASON_
#define _ULTRASON_
#include "librairies\Grove_Ultrasonic_Ranger-master\Ultrasonic.h" 

class Ultrason 
{
    unsigned long m_distance;

    public:
    Ultrason() 
    {
        m_distance = 0; //distance
    }

    Ultrasonic.ultrasonic(12);

    long GetDistance() const 
    {
        return m_distance; 
    }

    void Update()
    {
        delay(100);
        m_distance = ultrasonic.MeasureInCentimeters();
    }
};

#endif