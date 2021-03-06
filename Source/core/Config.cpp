/*
  ==============================================================================

    Config.cpp
    Created: 31 Oct 2018 9:39:16pm
    Author:  Jasmine Leblond-Chartrand

  ==============================================================================
*/

#include "Config.h"


std::shared_ptr<User> Config::user = nullptr;

//Current session parameters (Default init)
Partials::Options Config::partials = Partials::Options::all;
int Config::nbAmplitudeRatios = 2;
std::vector<int> Config::vecAudibleRanges {100};
int Config::baseFreq = 200;

//Current synthesis parameters (Default init)
int Config::nbPartials = 1;
int Config::waveTypeID = 1;

double Config::sampleRate = 0;

bool Config::isPlaying = false;
bool Config::hasStartedPlaying = false;

//Audio parameters
float Config::mainVolume = 1.0;

//Other parameters
double Config::soundDuration = 1000;
File Config::reportDirectory = File::getSpecialLocation(File::userDesktopDirectory);

