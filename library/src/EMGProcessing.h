#ifndef EMGPROCESSING_H
#define EMGPROCESSING_H

#include "Arduino.h"
#include "math.h"

enum FILTER_TYPE {LOWPASS_FILTER, HIGHPASS_FILTER};



class SecondOrderFilter
{
    public:        

        void init(int SAMPLE_RATE, FILTER_TYPE ftype);

        float update(float input);

    private:
        double num[3];
        double den[3];

};

class FourthOrderFilter
{
    public:

        void init(int SAMPLE_RATE, FILTER_TYPE ftype);

        float update(float input);

    private:
        float num[6];
        float den[6];
};

#endif