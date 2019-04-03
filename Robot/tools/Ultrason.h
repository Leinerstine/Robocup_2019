#ifndef _ULTRASON_
#define _ULTRASON_
#include "Ultrasonic.h"


class Ultrason 
{
    long m_distance; //distance obtenue par le capteur 
    unsigned long m_time; //temps 
    Ultrasonic m_us; //variable créée via Ultrasonic.h 

    public:
    Ultrason() : m_us(4)
    {
        m_distance = 0; //distance
        m_time = millis(); // on update le temps de base
    }

    long GetDistance() const 
    {
        return m_distance; //renvoi distance
    }

    void Update()
    {
        unsigned long NewTime = millis(); //nouvelle variable du nouveau temps
        if (NewTime < m_time+100) //on veut avoir le nouveau temps tous les dixièmes de seconde
             return;

        m_distance = m_us.MeasureInCentimeters(); //distance en centimetres
        m_time = NewTime; //on update le temps quand on a pris la mesure 
    }

};


#endif