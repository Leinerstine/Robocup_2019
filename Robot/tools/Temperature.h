#ifndef _TEMPERATURE_
#define _TEMPERATURE_

#include <math.h>
#include "rgb_lcd.h"
#define _ANALOG_THERMIC 0//à mettre l'adresse du capteur

class Temperature
{
    rgb_lcd         light; //création capteur
    float           m_temp; //température 
    const int R =   0; //valeurs couleurs
    const int G =   0;
    const int B =   0;
    bool            m_difference; //verifier si trop grande difference

    public:
    Temperature()
    {
        m_temp = 0; //initialisation température
        m_difference = false; //de base il n'y a pas de différence de température
    }

    void Setup()
    {
        light.begin(16,2); //initialisation capteur colonne ligne 
        light.setRGB(R, G, B); //initialisation couleur
    }

    float GetTemperature()
    {
        return m_temp;
    }

    void Update()
    {
        float volts = analogRead(_ANALOG_THERMIC); //on obtient la température en volts
        float New_Temp = 20.f - (volts - 25.f)*2.f; //on convertit moyennement en degrés

        if (New_Temp - m_temp > 5) //difference température 5 degrés
            m_difference = true;
        
        if(m_difference)
            light.setRGB(255,0,0); //on change la couleur background
            light.setCursor(0,1); //où afficher texte
            light.print("VICTIM FOUND");

        New_Temp = m_temp; //à la fin de chaque boucle : on modifie la valeur afin de pouvoir comparer avec la dernière valeur 

        delay(100);
    }
};



#endif 