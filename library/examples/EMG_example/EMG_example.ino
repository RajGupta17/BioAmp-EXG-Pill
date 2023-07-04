#include "Arduino.h"
#include "EMGFilters.h"

#define INPUT_PIN 32
#define BAUD_RATE 115200

EMGFilters object;

void setup() {
	Serial.begin(BAUD_RATE);
    object.init_EMG(500, true, true, true); //initialised Band-pass filter (50Hz to 200Hz) for Sample Rate of 500Hz
    
}


void loop()
{
    unsigned long long timeStamp = micros();

    float readings = analogRead(INPUT_PIN);
    float filteredReadings = object.update(readings);
}