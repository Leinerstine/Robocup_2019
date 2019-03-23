#ifndef _TEMPERATURE_
#define _TEMPERATURE_

#include <math.h>
#include "rgb_lcd.h"
#define _ANALOG_THERMIC 14//à mettre l'adresse du capteur

class Temperature
{
    rgb_lcd         light; //création capteur
    float           m_fTemp; //température 
    const int R =   0; //valeurs couleurs
    const int G =   0;
    const int B =   0;
    long            m_EndDisplayTime; //temps où éteindre l'affichage

    public:
    Temperature()
    {
        m_fTemp = 0.f; //initialisation température
    }

    void Setup()
    {
        light.begin(16,2); //initialisation capteur colonne ligne 
        light.setRGB(R, G, B); //initialisation couleur
        m_EndDisplayTime = 0;
    }

    float GetTemperature() const
    {
        return m_fTemp;
    }

    void Update()
    {
        float volts = analogRead(_ANALOG_THERMIC); //on obtient la température en volts
        float New_Temp = 20.f - (volts - 25.f)*2.f; //on convertit moyennement en degrés

        if (m_fTemp == 0.f) //initialise
            m_fTemp = New_Temp;

        if (New_Temp - m_fTemp > 5.f) //difference température 5 degrés
        {
           if (m_EndDisplayTime == 0) //pas d'affichage
           {
                m_EndDisplayTime = millis() + 5000; //temps actuel + 5 secondes (on coupe dans 5sec)
                light.setRGB(255,0,0); //on change la couleur background
                light.setCursor(0,1); //où afficher texte
                light.print("VICTIM FOUND");
           }
        }
 
        
        if(m_EndDisplayTime != 0) //si on affiche
        {
            if (m_EndDisplayTime < millis())
            {
                light.noDisplay();
                m_EndDisplayTime = 0;
            }
        }

        m_fTemp = New_Temp; //à la fin de chaque boucle : on modifie la valeur afin de pouvoir comparer avec la dernière valeur 
    }
};



#endif 