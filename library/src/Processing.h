#ifndef PROCESSING_H
#define PROCESSING_H

enum FILTER_TYPE {LOWPASS_FILTER, HIGHPASS_FILTER}

class SecondOrderFilter
{
    public:

    void init(int SAMPLE_RATE, FILTER_TYPE ftype);

    float update(float input);

    private:
    float num[3];
    float den[3];

};

class FourthOrderFilter
{
    public:

    void init(int SAMPLE_RATE, FILTER_TYPE ftype);

    float update(float input);

    private:
};