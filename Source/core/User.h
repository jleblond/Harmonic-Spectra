/*
  ==============================================================================

    User.h
    Created: 23 Oct 2018 1:41:57am
    Author:  Jasmine Leblond-Chartrand

  ==============================================================================
*/

#pragma once
#include "../JuceLibraryCode/JuceHeader.h"

#include "Session.h"

class User
{
public:
    User(String username) : m_username(username) {}
    
    std::vector<std::shared_ptr<Session>>& getVecSessions()
    {
        return m_vecSessions;
    }
    
    std::shared_ptr<Session>& getLastSession()
    {
        assert(m_vecSessions.size()>0);
        return m_vecSessions.back();
    }
    
    String getUsername()
    {
        return m_username;
    }
    
private:
    String m_username = "";
    std::vector<std::shared_ptr<Session>> m_vecSessions;
    
};