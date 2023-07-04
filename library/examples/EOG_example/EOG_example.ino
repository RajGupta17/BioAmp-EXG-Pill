#include "Arduino.h"
#include "EOGFilters.h"

#define BAUD_RATE 115200
#define INPUT_PIN 32

EOGFilters object;

void setup()
{
    Serial.begin(BAUD_RATE);
    object.init_EOG(500, true, true, false) //initialised High Pass Filter (x to y Hz) for Sample Rate of 500Hz
}


void loop()
{
    unsigned long long timeStamp = micros();

    float readings = analogRead(INPUT_PIN);
    float filteredReadings = object.update(readings);
}