#include "Arduino.h"
#include "EMGFilters.h"
#include "EMGProcessing.h"

#define INPUT_PIN 32
#define BAUD_RATE 115200
#define SAMPLE_RATE 500

EMGFilters object;

void setup()
{
	Serial.begin(BAUD_RATE);
  //object.init_EMG(500, true, true, true); //initialised Band-pass filter (50Hz to 200Hz) for Sample Rate of 500Hz
    
}


void loop()
{

  object.init_EMG(SAMPLE_RATE, false, true, true); //initialised Band-pass filter (50Hz to 200Hz) for Sample Rate of 500Hz
   static unsigned long past = 0;
	unsigned long present = micros();
	unsigned long interval = present - past;
	past = present;

	// Run timer
	static long timer = 0;
	timer -= interval;

  if(timer < 0){

    timer += 1000000 / SAMPLE_RATE; //sample rate = 500
  
    float readings = analogRead(INPUT_PIN);
    float filteredReadings = object.update(readings, SECOND_ORDER);
    Serial.print(readings);
    Serial.print(",");
    Serial.println(filteredReadings);

  }
}