/*
  ==============================================================================

    MainApplication.h
    Created: 23 Oct 2018 1:28:55am
    Author:  Jasmine Leblond-Chartrand

  ==============================================================================
*/

#pragma once

#include "../../JuceLibraryCode/JuceHeader.h"

#include "HeaderView.h"
#include "UserConfigView.h"
#include "ExerciseConfigView.h"
#include "MainWindow.h"
#include "QuestionsView.h"
#include "VolumeView.h"
#include "StatsView.h"

const int HEIGHT = 700;
const int WIDTH = 900;

const float HEADER_PERCENT_HEIGHT = 0.15;
const float BOTTOM_BUTTONS_HEIGHT = 0.20; //height relative to espace left without header


class MainApplication    : public Component,
                            public Button::Listener
{
public:
    
    MainApplication();

    ~MainApplication();

    void paint (Graphics& g) override;

    void resized() override;

    void buttonClicked(Button* button) override;
    
    void showUserConfig(bool isVisible);
    
    void showExerciseConfig(bool isVisible);

protected:
    LookAndFeel *m_LF = new LookAndFeel_V4( (LookAndFeel_V4::getLightColourScheme() ) );
    
    HeaderView m_headerView;
    UserConfigView m_userConfigView;
    ExerciseConfigView m_exerciseConfigView;
    
    TextButton m_createUserButton;
    TextButton m_startSessionButton;
    TextButton m_endSessionButton;
   
    
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainApplication)
};
