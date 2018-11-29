/*
  ==============================================================================

    ReportBuilder.h
    Created: 23 Oct 2018 1:41:20am
    Author:  Jasmine Leblond-Chartrand

  ==============================================================================
*/

#pragma once

#include "../../JuceLibraryCode/JuceHeader.h"

#include "Config.h"
//#include "Session.h"
#include "Report.h"

class ReportBuilder
{
public:
    ReportBuilder();
    ~ReportBuilder();
    
    static std::shared_ptr<Report> createReport();
    
    static void saveReport();
    

  
private:
   

   
};
