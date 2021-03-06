/*
  ==============================================================================

    Synthesis.cpp
    Created: 19 Dec 2017 1:12:58pm
    Author:  Jasmine Leblond-Chartrand

  ==============================================================================
*/

#include "Synthesis.h"

Synthesis Synthesis::m_synth = Synthesis();

Synthesis& Synthesis::Instance()
{
    return m_synth;
}

Synthesis::Synthesis()
    : m_sampleRate (0.0),
      m_amplitudeFactor(1.0),
      m_currentFundFrequency (20),
      m_waveType (11),
      m_nbPartials (1) //default nb at intialization
{
    
}

Synthesis::~Synthesis()
{
    
}

void Synthesis::setSampleRate (double sampleRate)
{
    m_sampleRate = sampleRate;
}

const double Synthesis::getSampleRate() const
{
    return m_sampleRate;
}

void Synthesis::setCurrentFundFrequency (int currFundFrequency)
{
    m_currentFundFrequency = currFundFrequency;
    
    std::cout<<"-- Synthesis::setCurrentFundFrequency(int currFundFrequency)"<<std::endl;
    std::cout<<"Synthesis::m_currentFundFrequency: "<<m_currentFundFrequency<<std::endl;
    
}

const int Synthesis::getCurrentFundFrequency() const
{
    return m_currentFundFrequency;
}

void Synthesis::setWaveType (int waveType)
{
    m_waveType = waveType;
}

const int Synthesis::getWaveType() const
{
    return m_waveType;
}

void Synthesis::setNbPartials (int nbPartials)
{
    m_nbPartials = nbPartials;
}


const int Synthesis::getNbPartials() const
{
    return m_nbPartials;
}

void Synthesis::setAmplitudeFactor(double amplitudeFactor)
{
    m_amplitudeFactor = amplitudeFactor;
}

const double Synthesis::getAmplitudeFactor() const
{
    return m_amplitudeFactor;
}

const std::vector<Partial>& Synthesis::getVecPartials() const
{
    return m_vecPartials;
}

void Synthesis::updateSynthesisValues()
{
    m_waveType = Config::waveTypeID;
    m_nbPartials = Config::nbPartials;
    
    std::cout<<"-- Synthesis::updateSynthesisValues()"<<std::endl;
    std::cout<<"Config::waveTypeID: "<<Config::waveTypeID<<" Config::nbPartials: "<<Config::nbPartials<<std::endl;
     std::cout<<"Synthesis::waveTypeID: "<<m_waveType<<" Synthesis::nbPartials: "<<m_nbPartials<<std::endl;
    
    fillVecPartials();
}


float Synthesis::getCurrentBufferSample()
{
    float currentSample = 0;
    
    
    if(m_vecPartials.size()== 1)  //sine wave case
    {
        float partialSample = (float) std::sin (m_vecPartials[0].angle);
        m_vecPartials[0].angle += m_vecPartials[0].angleDelta;
        currentSample += partialSample * m_vecPartials[0].amplitude * m_amplitudeFactor;
    }
    else if (m_vecPartials.size() > 1)
    {
        for (int i=0; i<m_nbPartials; i++)
        {
            float partialSample = (float) std::sin (m_vecPartials[i].angle);
            m_vecPartials[i].angle += m_vecPartials[i].angleDelta;
            currentSample += partialSample * m_vecPartials[i].amplitude * m_amplitudeFactor;
        }
    }
    
    return currentSample;
}


double Synthesis::getAngleDelta (double freq, double sampleRate)
{
    assert (sampleRate > 0.0);
    const double cyclesPerSample = freq / sampleRate;
    double angleDelta =  cyclesPerSample * 2.0 * double_Pi;
        
    return angleDelta;
}
    
    
void Synthesis::fillVecPartials ()
{
    m_vecPartials.clear();
    
    bool neg = false;
    
    
    if(m_waveType == 11)
    {
        double partialFreq = m_currentFundFrequency;
        double partialLevel = 1;
        
        m_vecPartials.push_back (
                                Partial ( partialFreq, partialLevel, getAngleDelta (partialFreq, m_sampleRate) )
                                );
        
    }
    else //waveType is not sine
    {
        
        for (int i=1; i<=m_nbPartials; i++)
        {
            double partialFreq = i*m_currentFundFrequency;
            double partialLevel = 0;

            
            switch (m_waveType)
            {
                    //SQUARE
                case 1:
                    if (i % 2 != 0)
                        partialLevel = 1/pow (i, 1);
                  //  std::cout<<"SQUARE"<<std::endl;
                    break;
                    
                case 2:
                    if (i % 2 != 0)
                        partialLevel = 1/pow (i, 1.25);
                 //   std::cout<<"SQUARE 2 TRI"<<std::endl;
                    break;
                    
                case 3:
                    if (i % 2 != 0)
                    {
                        partialLevel = 1/pow (i, 1.50);
                    }
                
                 //   std::cout<<"SQUARE 3 TRI"<<std::endl;
                    break;
                    
                case 4:
                    if (i % 2 != 0)
                    {
                        partialLevel = 1/pow (i, 1.75);
                    }

                  //  std::cout<<"SQUARE 4 TRI"<<std::endl;
                    break;
                    
                    //TRI
                case 5:
                    if (i % 2 != 0)
                    {
                        partialLevel = 1/pow (i, 2.0);
                        
                        if(neg)
                            partialLevel = -partialLevel;

                        neg = !neg;
                    }
                //    std::cout<<"TRI"<<std::endl;
                    break;
                    
                    //SAW
                case 6:
                    partialLevel = 1/pow (i, 1);
               //     std::cout<<"SAW 1"<<std::endl;
                    break;
                    // STEEPER SAW
                case 7:
                    partialLevel = 1/pow (i, 1.25);
               //     std::cout<<"SAW 2"<<std::endl;
                    break;
                    
                case 8:
                    partialLevel = 1/pow (i, 1.5);
                //    std::cout<<"SAW 3"<<std::endl;
                    break;
                    
                case 9:
                    partialLevel = 1/pow (i, 1.75);
                //    std::cout<<"SAW 4"<<std::endl;
                    break;
                
                case 10:
                    partialLevel = 1/pow (i, 2.0);
                 //   std::cout<<"SAW 5"<<std::endl;
                    break;

                    
            }; //switch
            
            
            m_vecPartials.push_back (
                                    Partial ( partialFreq, partialLevel, getAngleDelta (partialFreq, m_sampleRate) )
                                    );
        } //for loop
        
        
//            std::cout<<"-- Synthesis::fillVecPartials()"<<std::endl;
//            std::cout<<"-- Print all normalized partials in m_vecPartials"<<std::endl;
//            for(auto& i : m_vecPartials)
//            {
//                i.print();
//            }
        
        
    } //else
   
    normalizePartialsAmp(m_vecPartials);
    
    
}


void Synthesis::normalizePartialsAmp(std::vector<Partial>& vec)
{
    //First normalization to prevent clipping
    double sum = 0;
    
    for(const auto &partial : vec)
    {
        sum += partial.amplitude;
    }
    
    if(sum > 1)
    {
        for(auto &partial : vec)
        {
            partial.amplitude *= (1/sum);
        }
    }
    else if (sum > 0.9)  // 0.9 < sum < 1.0
        //added specifically for TRI WAVE whose partials sum is about 0.91 but still clips
    {
        
        for(auto &partial : vec)
        {
            partial.amplitude *= 0.7;
        }
    }
    
    
    // Second normalization based on subjective loudness
    for(auto &partial : vec)
    {
        partial.amplitude *= secondNormalization();
    }

    
}



float Synthesis::secondNormalization()
{
    float factor = 1;
   
    switch(m_waveType)
    {
        case 1:
            factor = 0.42;
            break;
            
        case 2:
            factor = 0.5;
            break;
            
        case 3:
            factor = 0.5;
            break;
            
        case 4:
            factor = 0.79;
            break;
            
        case 5:
            factor = 1;
            break;
            
        case 6:
            factor = 0.63;
            break;
            
        case 7:
            factor = 0.7;
            break;
            
        case 8:
            factor = 0.86;
            break;
            
        case 9:
            factor = 0.94;
            break;
            
        case 10:
            factor = 1;
            break;
    };
    
    return factor;
}
    

    

