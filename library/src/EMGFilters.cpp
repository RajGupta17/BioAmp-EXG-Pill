#include "EMGFilters.h"

                                           

SecondOrderFilter LPF_2nd;
SecondOrderFilter HPF_2nd;
FourthOrderFilter LPF_4th;
FourthOrderFilter HPF_4th;

void EMGFilters::init_EMG(int SAMPLE_RATE, bool enableNF, bool enableHPF, bool enableLPF)
{
    m_SAMPLE_RATE = SAMPLE_RATE; //updating values to use it in update member function
    m_enableNF = enableNF;
    m_enableLPF = enableLPF;
    m_enableHPF = enableHPF;

    // LPF_2nd.init(SAMPLE_RATE, LOWPASS_FILTER);
    // HPF_2nd.init(SAMPLE_RATE, HIGHPASS_FILTER);

    // LPF_4th.init(SAMPLE_RATE, LOWPASS_FILTER);
    // HPF_4th.init(SAMPLE_RATE, HIGHPASS_FILTER);

    if (enableHPF==true)
    {
        HPF_2nd.init(SAMPLE_RATE, HIGHPASS_FILTER);
        HPF_4th.init(SAMPLE_RATE, HIGHPASS_FILTER);
    }

    if (enableLPF==true)
    {
        LPF_2nd.init(SAMPLE_RATE, LOWPASS_FILTER);
        LPF_4th.init(SAMPLE_RATE, LOWPASS_FILTER);
    }


}

float EMGFilters::update(float inputValue, FILTER_ORDER order)
{
    float out;

    // if(m_enableNF==true)
    // {
    //     output = inputValue;
    // }

    if(m_enableHPF==true && (order == SECOND_ORDER)) // 2nd order High Pass Filter
    {
        out = HPF_2nd.update(inputValue);

    }
    
    if(m_enableLPF==true && (order == SECOND_ORDER)) // 2nd order Low Pass Filter
    {
        out = LPF_2nd.update(inputValue);
    }

    if(m_enableHPF==true && (order == FOURTH_ORDER)) // 4th order High Pass Filter
    {
        out = HPF_4th.update(inputValue);
    }

    if(m_enableLPF==true && (order == FOURTH_ORDER)) // 4th order Low Pass Filter
    {
        out = LPF_4th.update(inputValue);
    }

    // else if (m_enableHPF==false && m_enableLPF==false)
    // {
    //     output = inputValue;
    // } 

    return out;

}