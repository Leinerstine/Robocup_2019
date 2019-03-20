#ifndef _TEMPERATURE_
#define _TEMPERATURE_

#include <math.h>
#include "rgb_lcd.h"
#define _ANALOG_THERMIC 

class Temperature
{
    rgb_lcd         light;
    float           m_temp; //température 
    const int R =   255;
    const int G =   0;
    const int B =   0;
    bool            difference; //verifier si trop grande difference

    public:
    Temperature() g_Temp;
    {
        m_temp = 0; //initialisation température
        difference = false;
    }

    void setup()
    {
        light.begin(18,1); //colonnes, lignes
        light.setRGB(R, G, B);
    }

    float PrintMessage()
    {
        float volts = analogRead(_ANALOG_THERMIC);
        float m_temp = 20.f - (volts - 25.f)*2.f;
        float New_Temp = m_temp;

        if (New Temp - m_temp > 5)
            m_difference = true;
        
        if(m_difference)
            light.print("VICTIM FOUND");

        delay(100);
    }
};



#endif 