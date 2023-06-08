#include <filters.hpp>
#include <Arduino.h>


//Defining few macros 
#define BAUD_RATE 115200
#define DATA_LENGTH 16
#define INPUT_PIN 19
#define SAMPLE_RATE 75

bool peak_level = false;

void setup()
{
    Serial.begin(BAUD_RATE);

    pinMode(INPUT_PIN, INPUT);
}

void loop()
{


    Filters library; //declaring an object named library 
    library.EMG_read(SAMPLE_RATE,INPUT_PIN); //will access EMG readings

    float signal_read = library.EMG_read(SAMPLE_RATE,INPUT_PIN); //EMG readings stored in a variable

    Filters peak_value; //declaring an object named peak_value
    peak_value.Getpeak(signal_read, DATA_LENGTH); //Will access the peak values from the "Getpeak" function

    peak_level = peak_value.Getpeak(signal_read, DATA_LENGTH); 


/*These readings can be easily used further by calling the objects*/

}