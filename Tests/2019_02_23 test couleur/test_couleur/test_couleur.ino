//#include <Wire.h>
//#include <GroveColorSensor.h>
#include <Adafruit_TCS34725.h>


Adafruit_TCS34725 g_sensor;
 
#define CLK_PIN   7
#define DATA_PIN  8
#define NUM_LEDS  1            //The number of Chainable RGB LED


long g_lastTimeSensorStarted = 0;

void setup()
{
    Serial.begin(9600);
    g_sensor.begin();

    
    g_sensor.setInterrupt(true);
    g_lastTimeSensorStarted = millis();
}
 
void loop()
{
    int red, green, blue;
    //GroveColorSensor colorSensor;
//    colorSensor.ledStatus = 1;            // When turn on the color sensor LED, ledStatus = 1; When turn off the color sensor LED, ledStatus = 0.
    uint16_t  r,g,b,c;

    if (millis() > g_lastTimeSensorStarted+60)
    {
        //g_sensor.setInterrupt(true);
        //delay(60);
        g_sensor.getRawData(&r, &g, &b, &c);

        Serial.print("The RGB value are: RGB( ");
        Serial.print(r,DEC);
        Serial.print(", ");
        Serial.print(g,DEC);
        Serial.print(", ");
        Serial.print(b,DEC);
        Serial.print(", ");
        Serial.print(c,DEC);
        Serial.println(" )");
        
        g_sensor.clearInterrupt();

        g_sensor.setInterrupt(true);
        g_lastTimeSensorStarted = millis();
    }

   /* while(1)
    {
        colorSensor.readRGB(&red, &green, &blue);    //Read RGB values to variables.
        delay(300);
        Serial.print("The RGB value are: RGB( ");
        Serial.print(red,DEC);
        Serial.print(", ");
        Serial.print(green,DEC);
        Serial.print(", ");
        Serial.print(blue,DEC);
        Serial.println(" )");
        colorSensor.clearInterrupt();

        for(int i = 0; i<NUM_LEDS; i++)
        {
            leds.setColorRGB(i, red, green, blue);
        }
    } */ 
}
