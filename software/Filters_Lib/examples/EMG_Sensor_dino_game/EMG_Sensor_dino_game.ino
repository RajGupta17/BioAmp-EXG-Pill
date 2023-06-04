#include <Keyboard.h>
#include <filters.hpp>
#include <Arduino.h>
#include <HID_Buttons.h>

#define BAUD_RATE 115200
#define DATA_LENGTH 16
#define INPUT_PIN 36
#define EMG_THRESHOLD 100
#define SAMPLE_RATE 75

bool peak_level = false;
static unsigned long past_blink;
static unsigned long present_blink; 
long blink_interval;


void setup()
{
    Serial.begin(BAUD_RATE);
    Keyboard.begin();

    pinMode(INPUT_PIN, INPUT);
}

void loop()
{

    Filters library; //initiated an object named library 
    library.EMG_read(SAMPLE_RATE,INPUT_PIN); //will take EMG readings

    float signal_read = library.EMG_read(SAMPLE_RATE,INPUT_PIN); //EMG readings stored in a variable (SAMPLE RATE = 123)

    Filters peak_value; //initiated an object named peak_value
    peak_value.Getpeak(signal_read, DATA_LENGTH); //Will take the peak values from the "Getpeak" function

    peak_level = peak_value.Getpeak(signal_read, DATA_LENGTH);



    if (peak_level == true) //If peak is true then the spacebar will be pressed
    {
        Keyboard.press(32); //ASCII value for spacebar = 32
    }

    if (peak_level == false) //If false then release the spacebar 
    {
        Keyboard.release(32);
    }
}