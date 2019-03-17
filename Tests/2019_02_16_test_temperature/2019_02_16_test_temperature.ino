#include <math.h>

#define _ANALOG_THERMIC 0 //placement capteur

//pp
struct AllSensors
{
  float m_Temperature;
  float m_color;
};

AllSensors  g_AllSensors;

void setup() {
  Serial.begin(9600); //en série
}


float GetTemperature(int _analogInputId, bool _debug)
{
 #define B 3975
 
  float  a = analogRead(_analogInputId); //renvoie volts

  float t = 20.f - (a -25.f)*2.f;
   
  if (_debug)
  {

    Serial.print("Current temperature analogRead is ");
    Serial.println(a);
    Serial.print("Current temperature is ");
    Serial.println(t);
  }

  return t;
}

void DecideAvance(const AllSensors &_sensors)
{
  
}

void loop() 
{

  g_AllSensors.m_Temperature = GetTemperature(_ANALOG_THERMIC, false);

  DecideAvance(g_AllSensors);

  delay(1000);

}
