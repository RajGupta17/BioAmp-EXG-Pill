#ifndef EEGFILTERS_H
#define EEGFILTERS_H

class EEGFilters
{
    public:

    void init_EEG(int SAMPLE_RATE, bool enableNF=false, bool enableHPF = false, bool enableLPF = false);

    float update(float inputValue);

    private:
    int m_SAMPLE_RATE; //members
    bool m_enableNF=false;
    bool m_enableHPF = false;
    bool m_enableLPF = false;
};

#endif