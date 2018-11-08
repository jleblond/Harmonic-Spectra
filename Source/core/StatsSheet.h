/*
  ==============================================================================

    StatsSheet.h
    Created: 23 Oct 2018 1:43:43am
    Author:  Jasmine Leblond-Chartrand

  ==============================================================================
*/

#pragma once

struct StatsValue
{
    int count = 0;
    float percent = 0.0;
};


struct StatsSheet
{
    std::vector<StatsValue> vecWaves;
    StatsValue audibleRange;
    
    float score = -1;
    float percentTotalScore = 0;
    float maxScore = 100;
    float weightedAverage = 0;
    int countInvolvedValues = 0;
    int questionsCount = 0 ;
    
    
    StatsSheet()
    {
        for(int i=0;i<10;i++)
        {
            vecWaves.push_back(StatsValue());
        }
    }
};
