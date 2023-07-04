#include "EMGFilters.h"
#include "Processing.h"

//define coefficients here (For 200 Hz LPF and 50Hz HPF)
//SAMPLE RATE = 500Hz (2nd order)
float lpf_a00 = 1.00000000;
float lpf_a01 = 1.14298050;
float lpf_a02 = 0.41280160;
float lpf_b00 = 0.63894553;
float lpf_b01 = 1.27789105;
float lpf_b02 = 0.63894553;
//SAMPLE RATE = 1000Hz (2nd order)
float lpf_a10 = 1.00000000;
float lpf_a11 = -0.36952738;
float lpf_a12 = 0.19581571;
float lpf_b10 = 0.20657208;
float lpf_b11 = 0.41314417;
float lpf_b12 = 0.20657208;

//SAMPLE RATE = 500Hz (2nd order)
float hpf_a00 = 1.00000000;
float hpf_a01 = -1.14298050;
float hpf_a02 = 0.41280160;
float hpf_b00 = 0.63894553;
float hpf_b01 = -1.27789105;
float hpf_b02 = 0.63894553;
//SAMPLE RATE = 1000Hz (2nd order)
float hpf_a10 = 1.00000000;
float hpf_a11 = -1.56101808;
float hpf_a12 = 0.64135154;
float hpf_b10 = 0.80059240;
float hpf_b11 = -1.60118481;
float hpf_b12 = 0.80059240;

//SAMPLE RATE = 500Hz (4th order)
float lpf_c00 = 1.00000000;
float lpf_c01 = 1.04859958;
float lpf_c02 = 0.29614036;
float lpf_c03 = 1.00000000;
float lpf_c04 = 1.32091343;
float lpf_c05 = 0.63273879;
float lpf_d00 = 0.43284664;
float lpf_d01 = 0.86569329;
float lpf_d02 = 0.43284664;
float lpf_d03 = 1.00000000;
float lpf_d04 = 2.00000000;
float lpf_d05 = 1.00000000;

//SAMPLE RATE = 1000Hz (4th order)
float lpf_c10 = 1.00000000;
float lpf_c11 = -0.32897568;
float lpf_c12 = 0.06458765;
float lpf_c13 = 1.00000000;
float lpf_c14 = -0.45311952;
float lpf_c15 = 0.46632557;
float lpf_d10 = 0.04658291;
float lpf_d11 = 0.09316581;
float lpf_d12 = 0.04658291;
float lpf_d13 = 1.00000000;
float lpf_d14 = 2.00000000;
float lpf_d15 = 1.00000000;

//SAMPLE RATE = 500Hz (4th order)
float hpf_c00 = 1.00000000;
float hpf_c01 = -1.04859958;
float hpf_c02 = 0.29614036;
float hpf_c03 = 1.00000000;
float hpf_c04 = -1.32091343;
float hpf_c05 = 0.63273879;
float hpf_d00 = 0.43284664;
float hpf_d01 = -0.86569329;
float hpf_d02 = 0.43284664;
float hpf_d03 = 1.00000000;
float hpf_d04 = -2.00000000;
float hpf_d05 = 1.00000000;

//SAMPLE RATE = 1000Hz (4th order)
float hpf_c10 = 1.00000000;
float hpf_c11 = -1.47967422;
float hpf_c12 = 0.55582154;
float hpf_c13 = 1.00000000;
float hpf_c14 = -1.70096433;
float hpf_c15 = 0.78849974;
float hpf_d10 = 0.66201584;
float hpf_d11 = -1.32403167;
float hpf_d12 = 0.66201584;
float hpf_d13 = 1.00000000;
float hpf_d14 = -2.00000000;
float hpf_d15 = 1.00000000;
                                           

SecondOrderFilter LPF_2nd;
SecondOrderFilter HPF_2nd;
FourthOrderFilter LPF_4th;
FourthOrderFilter HPF_4th;

void EMGFilters::init_EMG(int SAMPLE_RATE, bool enableNF=false, bool enableHPF = false, bool enableLPF = false)
{
    m_SAMPLE_RATE = SAMPLE_RATE; //updating values to use it in update member function
    m_enableNF = enableNF;
    m_enableLPF = enableLPF;
    m_enableHPF = enableHPF;

    LPF_2nd.init(SAMPLE_RATE, LOWPASS_FILTER);
    HPF_2nd.init(SAMPLE_RATE, HIGHPASS_FILTER);

    LPF_4th.init(SAMPLE_RATE, LOWPASS_FILTER);
    HPF_4th.init(SAMPLE_RATE, HIGHPASS_FILTER);


}

float EMGFilters::update(float inputValue, FILTER_ORDER order)
{
    float output = 0;

    if(m_enableNF==true)
    {
        output = inputValue;
    }
    
    if(m_enableLPF==true && (order == SECOND_ORDER)) // 2nd order Low Pass Filter
    {
        output = LPF_2nd.update(output);
    }

    if(m_enableHPF==true && (order == SECOND_ORDER)) // 2nd order High Pass Filter
    {
        output = HPF_2nd.update(output);
    }

    if(m_enableLPF==true && (order == FOURTH_ORDER)) // 4th order Low Pass Filter
    {
        output = LPF_2nd.update(output);
    }

    if(m_enableHPF==true && (order == FOURTH_ORDER)) // 4th order High Pass Filter
    {
        output = HPF_2nd.update(output);
    }


}