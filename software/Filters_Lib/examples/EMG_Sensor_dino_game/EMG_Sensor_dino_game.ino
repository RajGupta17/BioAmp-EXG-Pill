#include <filters.hpp>
#include <Arduino.h>
#include "Keyboard.h"

#define BAUD_RATE 115200
#define DATA_LENGTH 16
#define EMG_THRESHOLD 100

bool peak = false;


void setup()
{
    Serial.begin(BAUD_RATE);
    Keyboard.begin();
}

void loop()
{
    Filters library;
    library.EMG_read(123,12);

    int signal_read = library.EMG_read(123,12);

    Filters peak;
    peak.Getpeak(signal_read);


    if (peak==true)
    {
        Keyboard.press(65);
        delay(50);
        Keyboard.release(65);
    }
}
