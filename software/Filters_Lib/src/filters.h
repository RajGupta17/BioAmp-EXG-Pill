#ifndef FILTERS_H
#define FILTERS_H

#include "Arduino.h"

class Filters
{
    public:

        float timer();
        bool Getpeak(float new_sample, int DATA_LENGTH);

        float ECG_read(int SAMPLE_RATE, int INPUT_PIN);
        float EMG_read(int SAMPLE_RATE, int INPUT_PIN);
        float EOG_read(int SAMPLE_RATE, int INPUT_PIN);
        float EEG_read(int SAMPLE_RATE, int INPUT_PIN);
        
        float ECGFilter(float input);
        float EEGFilter(float input);
        float EMGFilter(float input);
        float EOGFilter(float input);

    private:
        int SAMPLE_RATE;
        int INPUT_PIN;
};

#endif