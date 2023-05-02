#ifndef FILTERS_HPP
#define FILTERS_HPP

#include "Arduino.h"

class Filters
{
    public:
        void loop_ECG(int SAMPLE_RATE, int INPUT_PIN);
        void loop_EMG(int SAMPLE_RATE, int INPUT_PIN);
        void loop_EOG(int SAMPLE_RATE, int INPUT_PIN);
        void loop_EEG(int SAMPLE_RATE, int INPUT_PIN);
        
        float ECGFilter(float input);
        float EEGFilter(float input);
        float EMGFilter(float input);
        float EOGFilter(float input);

    private:
        int SAMPLE_RATE;
        int INPUT_PIN;
};

#endif