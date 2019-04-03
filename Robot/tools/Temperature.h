#ifndef _TEMPERATURE_
#define _TEMPERATURE_

#include <math.h>
#include "rgb_lcd.h"
#define _ANALOG_THERMIC 14 
#define _TEMP_UPDATE_DELTA_TIME_ 100 // ms

class Temperature
{
    rgb_lcd         light; //création capteur
    float           m_fMinTemp; //température 
    float           m_fCurrentTemp; //température 
    const int R =   0; //valeurs couleurs
    const int G =   0;
    const int B =   0;
    long            m_EndDisplayTime; //temps où éteindre l'affichage
    long            m_TimeToUpdate; 

    public:
    Temperature()
    {
        m_fMinTemp = 0.f; //initialisation température
        m_fCurrentTemp = 0.f;
    }

    void Setup()
    {
        light.begin(16,2); //initialisation capteur colonne ligne 
        light.setRGB(R, G, B); //initialisation couleur
        m_EndDisplayTime = 0;
        m_TimeToUpdate = millis(); // force premier update
    }

    float GetTemperature() const
    {
        return m_fCurrentTemp;
    }

    void Update()
    {
        if (m_TimeToUpdate >millis()) //pas d'update  
            return;
        m_TimeToUpdate = millis() + _TEMP_UPDATE_DELTA_TIME_;

        float volts = analogRead(_ANALOG_THERMIC); //on obtient la température en volts
        float New_Temp = 20.f - (volts - 25.f)*2.f; //on convertit moyennement en degrés

        if (m_fMinTemp == 0.f) //initialise
        {
            m_fMinTemp = New_Temp;
            m_fCurrentTemp = New_Temp;
        }

        if (New_Temp - m_fMinTemp > 2.f) //difference température 2 degrés
        {
           if (m_EndDisplayTime == 0) //pas d'affichage
           {
                light.clear();
                m_EndDisplayTime = millis() + 5000; //temps actuel + 5 secondes (on coupe dans 5sec)
                light.setRGB(R,255,B); //on change la couleur background
                light.print("VICTIM FOUND");
           }
        }
 
        
        if(m_EndDisplayTime != 0) //si on affiche
        {
            if (m_EndDisplayTime < millis()) //temps actuel > temps d'affichage
            {
                light.clear(); //plus de texte
                m_EndDisplayTime = 0;
            }
        }

        if (New_Temp<m_fMinTemp && New_Temp!=0.f)
            m_fMinTemp = New_Temp;
        m_fCurrentTemp = New_Temp; //à la fin de chaque boucle : on modifie la valeur afin de pouvoir comparer avec la dernière valeur 
    }

    void  DrawDebug(const char *_txt)
    {
        if(m_EndDisplayTime != 0) //si on affiche
           return;
        light.setRGB(255,G,B); //on change la couleur background
        light.setCursor(0,1); //où afficher texte
        light.print(_txt);
    }
};



#endif 