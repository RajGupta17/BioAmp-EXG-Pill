#ifndef FILTERS_HPP
#define FILTERS_HPP

#include "Arduino.h"

class Filters
{
    public:
        void loop(int SAMPLE_RATE, int INPUT_PIN);
        float ECGFilter(float input);
        float EEGFilter(float input);
        float EMGFilter(float input);
        float EOGFilter(float input);

    private:
        int SAMPLE_RATE;
        int INPUT_PIN;
};

#endif