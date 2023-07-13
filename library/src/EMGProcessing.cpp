#include "EMGProcessing.h"

                                         
double lpf_2nd_denominator_coef[2][3] = {{1.00000000, 1.14298050, 0.41280160},
                                           {1.00000000, -0.36952738, 0.19581571}};

double lpf_2nd_numerator_coef[2][3] = {{0.63894553, 1.27789105, 0.63894553},
                                         {0.20657208, 0.41314417, 0.20657208}};
                                    
double hpf_2nd_denominator_coef[2][3] = {{1.00000000, -1.14298050, 0.41280160},
                                           {1.00000000, -1.56101808, 0.64135154}};
                                           
double hpf_2nd_numerator_coef[2][3] = {{0.63894553, -1.27789105, 0.63894553},
                                         {0.80059240, -1.60118481, 0.80059240}};


double lpf_4th_denominator_coef[2][6] = {{1.00000000, 1.04859958, 0.29614036, 1.00000000, 1.32091343, 0.63273879},
                                               {1.00000000, -0.32897568, 0.06458765, 1.00000000, -0.45311952, 0.46632557}};

double lpf_4th_numerator_coef[2][6] = {{0.43284664, 0.86569329, 0.43284664, 1.00000000, 2.00000000, 1.00000000},
                                             {0.04658291, 0.09316581, 0.04658291, 1.00000000, 2.00000000, 1.00000000}};                                 

double hpf_4th_denominator_coef[2][6] = {{1.00000000, -1.04859958, 0.29614036, 1.00000000, -1.32091343, 0.63273879},
                                               {1.00000000, -1.47967422, 0.55582154, 1.00000000, -1.70096433, 0.78849974}};

double hpf_4th_numerator_coef[2][6] = {{0.43284664, -0.86569329, 0.43284664, 1.00000000, -2.00000000, 1.00000000},
                                             {0.66201584, -1.32403167, 0.66201584, 1.00000000, -2.00000000, 1.00000000}};


void SecondOrderFilter::init(int SAMPLE_RATE, FILTER_TYPE ftype)
{
    //double num[3];
    //double den[3];


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
    
    float output = input;
    {
        // Serial.print(input);
        // Serial.print(",");

        float z1, z2;
        float x = (output - (den[1]*z1) - (den[2]*z2))/(den[0]);
        output = (num[0]*x) + (num[1]*z1) + (num[2]*z2);
        // save last states
        z2 = z1;
        z1 = x;

        // Serial.print(den[1]);
        // Serial.print(",,");
        // Serial.print(z2);
        // Serial.print(",,,");
        // Serial.print(x);
        // Serial.print(",,,,");
        // Serial.print(output);
        // Serial.print(",,,,,");

    }
    return output;
}


void FourthOrderFilter::init(int SAMPLE_RATE, FILTER_TYPE ftype)
{
    //code
    //double num[6];
    //double den[6];


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
    float output = input;
    //float StageIn = 0;
    //float StageOut = 0;

    {
        static float z1, z2;
        float x = (output - den[1] * z1 - den[2] * z2) / den[0];
        float output = num[0] * x + num[1] * z1 + num[2] * z2;
        // save last states
        z2 = z1;
        z1 = x;
    }

    {
        static float z1, z2;
        float x = (output - den[4] * z1 - den[5] * z2) / den[3];
        float output = num[3] * x + num[4] * z1 + num[5] * z2;
        // save last states
        z2 = z1;
        z1 = x;
    }
    return output;
}