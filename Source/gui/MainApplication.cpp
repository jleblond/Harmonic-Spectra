/*
  ==============================================================================

    MainApplication.cpp
    Created: 31 Oct 2018 8:23:57pm
    Author:  Jasmine Leblond-Chartrand

  ==============================================================================
*/

#include "MainApplication.h"



MainApplication::MainApplication()
{
    //setSize (WIDTH, HEIGHT);
    //setLookAndFeel( m_LF );
    
        
    addAndMakeVisible(m_headerView);
    
    addAndMakeVisible(m_userConfigView);
    addAndMakeVisible(m_createUserButton);
    m_createUserButton.setButtonText("NEXT");
    m_createUserButton.addListener(this);
        
    addAndMakeVisible(m_exerciseConfigView);
    m_exerciseConfigView.setVisible(false);
    addAndMakeVisible(m_startSessionButton);
    m_startSessionButton.setButtonText("START");
    m_startSessionButton.addListener(this);
    m_startSessionButton.setVisible(false);
    
    addAndMakeVisible(m_mainWindow);
    m_mainWindow.setVisible(false);
    addAndMakeVisible(m_statsView);
    m_statsView.setVisible(false);
   // addAndMakeVisible(m_volumeView);
   // m_volumeView.setVisible(false);
    
    addAndMakeVisible(m_endSessionButton);
    m_endSessionButton.setColour(TextButton::buttonColourId, Colour (0xff003F5F));
    m_endSessionButton.setColour(TextButton::textColourOffId, Colours::white);
    m_endSessionButton.addListener(this);
    m_endSessionButton.setVisible(false);
    
    m_mainWindow.m_answerButton.addListener(this);
    
}
    
MainApplication::~MainApplication()
{
    //delete m_LF;
}
    
void MainApplication::paint (Graphics& g)
{
        
    g.fillAll (getLookAndFeel().findColour (ResizableWindow::backgroundColourId));   // clear the background
        
    g.setColour (Colours::grey);
    g.drawRect (getLocalBounds(), 1);   // draw an outline around the component
        
    g.setColour (Colours::white);
    g.setFont (14.0f);
    g.drawText ("MainApplication", getLocalBounds(),
                Justification::centred, true);   // draw some placeholder text
}
    
void MainApplication::resized()
{
    m_endSessionButton.setBounds (getWidth() - 0.05 -  ENDSESSIONBUTTON_WIDTH*getWidth(), 0, ENDSESSIONBUTTON_WIDTH*getWidth(), 0.03*getHeight());
    
    Rectangle<int> area (getLocalBounds());
    m_headerView.setBounds (area.removeFromTop( HEADER_PERCENT_HEIGHT*getHeight()));
        
    Rectangle<int> area1 (area);
    m_createUserButton.setBounds (area1.removeFromBottom(BOTTOM_BUTTONS_HEIGHT*getHeight()));
    m_userConfigView.setBounds(area1);
        
    Rectangle<int> area2 (area);
    m_startSessionButton.setBounds (area2.removeFromBottom(BOTTOM_BUTTONS_HEIGHT*getHeight()));
    m_exerciseConfigView.setBounds(area2);
        
    Rectangle<int> area3 (area);
    m_statsView.setBounds(area3.removeFromBottom(STATSVIEW_HEIGHT*getHeight()));
   // m_volumeView.setBounds (area3.removeFromRight(VOLUMEVIEW_WIDTH*getWidth()));
    m_mainWindow.setBounds(area3);
        
}
    
void MainApplication::buttonClicked(Button* button)
{
    if(button == &m_createUserButton)
    {
        String username = m_userConfigView.getTextFieldValue();
        Config::user = std::make_shared<User>(username);
        m_headerView.setUserLabel(username);
        
        displayPanel(1);
    }
    if(button == &m_startSessionButton)
    {
        Config::partials = m_exerciseConfigView.getPartials();
        Config::nbAmplitudeRatios = m_exerciseConfigView.getNbAmplitudeRatios();
        Config::vecAudibleRanges = m_exerciseConfigView.getVecAudibleRange();
        
        int baseFreq = m_exerciseConfigView.getBaseFreq();
        Config::baseFreq = baseFreq;
        Synthesis::Instance().setCurrentFundFrequency(baseFreq);
        
        Config::user->createSession(Config::partials, Config::nbAmplitudeRatios, Config::baseFreq, Config::vecAudibleRanges);
        
        displayPanel(2);
    }
    
    if(button == &m_endSessionButton)
    {
        //hide curr windows
        
        //report generation options

        m_mainWindow.resetAll(); //includes both GUI and m_ values (for waveType and audibleRange)
        displayPanel(3);
    }
    
    
    if (button == &m_mainWindow.m_answerButton)
    {
        m_statsView.repaint();
    }

    
}

void MainApplication::displayPanel(int panelNb)
{
    switch(panelNb)
    {
        case 1: //Pressing 'create user' -> Exercise config
            showUserConfig(false);
            showExerciseConfig(true);
            break;
        case 2: //Pressing 'new session' -> Main Window
            showExerciseConfig(false);
            showMainWindow(true);
            m_endSessionButton.setVisible(true);
            m_mainWindow.updateMatrixView();
            m_mainWindow.displayPanel(1);
            break;
        case 3: //Pressing 'end session' -> ExerciseConfig view
            showMainWindow(false);
            showExerciseConfig(true);
            m_endSessionButton.setVisible(false);
            break;
    };
}
    
void MainApplication::showUserConfig(bool isVisible)
{
    m_userConfigView.setVisible(isVisible);
    m_createUserButton.setVisible(isVisible);
}
    
void MainApplication::showExerciseConfig(bool isVisible)
{
    m_exerciseConfigView.setVisible(isVisible);
    m_startSessionButton.setVisible(isVisible);
}

void MainApplication::showMainWindow(bool isVisible)
{
    m_mainWindow.setVisible(isVisible);
    m_statsView.setVisible(isVisible);
   // m_volumeView.setVisible(isVisible);
}

