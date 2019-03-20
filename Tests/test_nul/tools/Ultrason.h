#ifndef _ULTRASON_
#define _ULTRASON_
#include "Ultrasonic.h"


class Ultrason 
{
    long m_distance;
    unsigned long m_time;
    Ultrasonic m_us;

    public:
    Ultrason() : m_us(12)
    {
        m_distance = 0; //distance
        m_time = millis();
    }

    long GetDistance() const 
    {
        return m_distance; 
    }

    void Update()
    {
        unsigned long NewTime = millis();
        if (NewTime < m_time+100)
             return;

        m_distance = m_us.MeasureInCentimeters();
        m_time = NewTime;
    }
};


#endif