#ifndef EMGFILTERS_H
#define EMGFILTERS_H

#include "Arduino.h"
#include "EMGProcessing.h"

enum FILTER_ORDER {SECOND_ORDER, FOURTH_ORDER};


class EMGFilters{

    public:

        void init_EMG(int SAMPLE_RATE, bool enableNF=false, bool enableHPF = false, bool enableLPF = false);

        float update(float inputValue, FILTER_ORDER order);

    private:
        int m_SAMPLE_RATE; //members
        bool m_enableNF= false;
        bool m_enableHPF = false;
        bool m_enableLPF = false;
};

#endif
