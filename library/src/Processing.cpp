#include "Processing.h"

//coefficients a, b are denominator and numerator coefficients respectively of 2nd order IIR Filter
//coefficients c, d are denominator and numerator coefficients respectively of 4th order IIR Filter

//lpf coeff (2nd order)
float lpf_a00, lpf_a01, lpf_a02, lpf_a10, lpf_a11, lpf_a12;
float lpf_b00, lpf_b01, lpf_b02, lpf_b10, lpf_b11, lpf_b12;

//hpf coeff (2nd order)
float hpf_a00, hpf_a01, hpf_a02, hpf_a10, hpf_a11, hpf_a12;
float hpf_b00, hpf_b01, hpf_b02, hpf_b10, hpf_b11, hpf_b12;

//lpf coeff (4th order)
float lpf_c00, lpf_c01, lpf_c02, lpf_c03, lpf_c04, lpf_c05, lpf_c10, lpf_c11, lpf_c12, lpf_c13, lpf_c14, lpf_c15;
float lpf_d00, lpf_d01, lpf_d02, lpf_d03, lpf_d04, lpf_d05, lpf_d10, lpf_d11, lpf_d12, lpf_d13, lpf_d14, lpf_d15;

//hpf coeff (4th order)
float hpf_c00, hpf_c01, hpf_c02, hpf_c03, hpf_c04, hpf_c05, hpf_c10, hpf_c11, hpf_c12, hpf_c13, hpf_c14, hpf_c15;
float hpf_d00, hpf_d01, hpf_d02, hpf_d03, hpf_d04, hpf_d05, hpf_d10, hpf_d11, hpf_d12, hpf_d13, hpf_d14, hpf_d15;

                                         
static float lpf_2nd_denominator_coef[2][3] = {{lpf_a00, lpf_a01, lpf_a02},
                                           {lpf_a10, lpf_a11, lpf_a12}};

static float lpf_2nd_numerator_coef[2][3] = {{lpf_b00, lpf_b01, lpf_b02},
                                         {lpf_b10, lpf_b11, lpf_b12}};
                                    
static float hpf_2nd_denominator_coef[2][3] = {{hpf_a00, hpf_a01, hpf_a02},
                                           {hpf_a10, hpf_a11, hpf_a12}};
                                           
static float hpf_2nd_numerator_coef[2][3] = {{hpf_b00, hpf_b01, hpf_b02},
                                         {hpf_b10, hpf_b11, hpf_b12}};


static float lpf_4th_denominator_coef[2][6] = {{lpf_c00, lpf_c01, lpf_c02, lpf_c03, lpf_c04, lpf_c05},
                                               {lpf_c10, lpf_c11, lpf_c12, lpf_c13, lpf_c14, lpf_c15}};

static float lpf_4th_numerator_coef[2][6] = {{lpf_d00, lpf_d01, lpf_d02, lpf_d03, lpf_d04, lpf_d05},
                                             {lpf_d10, lpf_d11, lpf_d12, lpf_d13, lpf_d14, lpf_d15}};                                 

static float hpf_4th_denominator_coef[2][6] = {{hpf_c00, hpf_c01, hpf_c02, hpf_c03, hpf_c04, hpf_c05},
                                               {hpf_c10, hpf_c11, hpf_c12, hpf_c13, hpf_c14, hpf_c15}};

static float hpf_4th_numerator_coef[2][6] = {{hpf_d00, hpf_d01, hpf_d02, hpf_d03, hpf_d04, hpf_d05},
                                             {hpf_d10, hpf_d11, hpf_d12, hpf_d13, hpf_d14, hpf_d15}};


void SecondOrderFilter::init(int SAMPLE_RATE, FILTER_TYPE ftype)
{
    float num[3];
    float den[3];

    if (ftype == LOWPASS_FILTER)
    {
        if (SAMPLE_RATE == 500)
        {
            for (int i = 0; i < 3; i++)
            {
                num[i] = lpf_2nd_numerator_coef[0][i];
                den[i] = lpf_2nd_denominator_coef[0][i];
            }
            
        }
        else if (SAMPLE_RATE == 1000)
        {
            for (int i = 0; i < 3; i++)
            {
                num[i] = lpf_2nd_numerator_coef[1][i];
                den[i] = lpf_2nd_denominator_coef[1][i];
            }
            
        }
    }

    else if (ftype == HIGHPASS_FILTER)
    {
        if (SAMPLE_RATE == 500)
        {
            for (int i = 0; i < 3; i++)
            {
                num[i] = hpf_2nd_numerator_coef[0][i];
                den[i] = hpf_2nd_denominator_coef[0][i];
            }
            
        }
        else if (SAMPLE_RATE == 1000)
        {
            for (int i = 0; i < 3; i++)
            {
                num[i] = hpf_2nd_numerator_coef[1][i];
                den[i] = hpf_2nd_denominator_coef[1][i];
            }
            
        }
    }
}


float SecondOrderFilter::update(float input)
{
    float z1=0, z2=0;
    float output = input;

    {
        float x = (output - den[1] * z1 - den[2] * z2) / den[0];
        float output = num[0] * x + num[1] * z1 + num[2] * z2;
        // save last states
        z2 = z1;
        z1 = x;
    }
    return output;
}

SecondOrderFilter out; //object for cascading 

void FourthOrderFilter::init(int SAMPLE_RATE, FILTER_TYPE ftype)
{
    //code
    float num[6];
    float den[6];

    if (ftype == LOWPASS_FILTER)
    {
        if (SAMPLE_RATE == 500)
        {
            for(int i=0; i<6; i++)
            {
                num[i] = lpf_2nd_numerator_coef[0][i];
                den[i] = lpf_2nd_denominator_coef[0][i];
            }
        }

        if (SAMPLE_RATE == 1000)
        {
            for (int i=0; i<6; i++)
            {
                num[i] = lpf_2nd_numerator_coef[1][i];
                den[i] = lpf_2nd_denominator_coef[1][i];
            }
        }
    }

    if (ftype == HIGHPASS_FILTER)
    {
        if (SAMPLE_RATE == 500)
        {
            for (int i =0; i<6; i++)
            {
                num[i] = hpf_2nd_numerator_coef[0][i];
                den[i] = hpf_2nd_denominator_coef[0][i];
            }
        }

        if (SAMPLE_RATE == 1000)
        {
            for (int i=0; i<6; i++)
            {
                num[i] = hpf_2nd_numerator_coef[1][i];
                den[i] = hpf_2nd_denominator_coef[1][i];
            }
        }
    }

}


float FourthOrderFilter::update(float input)
{
    //code
    float z1=0, z2=0;
    float output = input;
    //float StageIn = 0;
    //float StageOut = 0;

    {
        float x = (output - den[1] * z1 - den[2] * z2) / den[0];
        float output = num[0] * x + num[1] * z1 + num[2] * z2;
        // save last states
        z2 = z1;
        z1 = x;
    }

    {
        float x = (output - den[4] * z1 - den[5] * z2) / den[3];
        float output = num[3] * x + num[4] * z1 + num[5] * z2;
        // save last states
        z2 = z1;
        z1 = x;
    }
    return output;
}