#include "Ultrasonic.h"

Ultrasonic ultrasonic(7);
void setup()
{
    Serial.begin(9600);
}
void loop()
{
    long RangeInCentimeters;

    Serial.println("The distance to obstacles in front is: ");
    RangeInCentimeters = ultrasonic.MeasureInCentimeters(); // two measurements should keep an interval
    Serial.print(RangeInCentimeters);//0~400cm
    Serial.println(" cm");
    delay(2000);
}
