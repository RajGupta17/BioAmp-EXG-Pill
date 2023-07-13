#ifndef ECGFILTERS_H
#define ECGFILTERS_H


class ECGFilters
{
    public:

    void init_ECG(int SAMPLE_RATE, bool enableNF=false, bool enableHPF = false, bool enableLPF = false);

    float update(float inputValue);

    private:
    int m_SAMPLE_RATE; //members
    bool m_enableNF=false;
    bool m_enableHPF = false;
    bool m_enableLPF = false;
};

#endif