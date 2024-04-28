#include "Manager.h"
#include "Component.h"
#include "Comments.h"
#include "Encryption.h"
#include "Enters.h"
#include "Junker.h"
#include "Looper.h"
#include "Parser.h"
#include "Spaces.h"
#include "Renamer.h"

#include <iostream>
#include <vector>
#include <string>

Manager::Manager()
{
}

Manager::~Manager()
{
    for (int i = 0; i < m_components.size(); i++)
    {
        delete m_components[i];
    }
    m_components.clear();
    m_activeComponents.clear();
}

void Manager::AddComponent(Component* component, bool active=false)
{
    m_components.push_back(component);
    m_activeComponents.push_back(active);
}

void Manager::StateComponent(Component* component, bool state)
{
    for (int i = 0; i < m_components.size(); i++)
    {
        if (m_components[i] == component)
        {
            m_activeComponents[i] = state;
            //break;
        }
    }
}

void Manager::StateComponent(std::string tag, bool state)
{
    for (int i = 0; i < m_components.size(); i++)
    {
        if (m_components[i]->GetTag() == tag)
        {
            m_activeComponents[i] = state;
        }
    }
}

void Manager::RemoveComponent(Component* component)
{
    for(int i = 0; i < m_components.size(); i++)
    {
        if (m_components[i] == component)
        {
            delete m_components[i];
            m_components.erase(m_components.begin() + i);
            m_activeComponents.erase(m_activeComponents.begin() + i);
            break;
        }
    }

}

void Manager::DefaultSetup(std::vector<std::wstring>* p_ContentFile)
{
    if(p_ContentFile == nullptr)
        return;
    
    if(m_components.size() > 0)
    {
        for (int i = 0; i < m_components.size(); i++)
        {
            delete m_components[i];
        }
        m_components.clear();
        m_activeComponents.clear();
    }

    //todo: check if change order Comments with Parser
    AddComponent(new Comments(p_ContentFile));
    Parser* parser = new Parser(p_ContentFile);
    AddComponent(parser);
    AddComponent(new Looper(p_ContentFile));
    AddComponent(new Junker(p_ContentFile, parser));
    AddComponent(new Renamer(p_ContentFile, parser));
    AddComponent(new Encryption(p_ContentFile));
    AddComponent(new Enters(p_ContentFile));
    AddComponent(new Spaces(p_ContentFile));

}

Component* Manager::GetComponent(std::string tag)
{
    for (int i = 0; i < m_components.size(); i++)
        if (m_components[i]->GetTag() == tag)
            return m_components[i];
    return nullptr;
}

std::vector<Component*>* Manager::GetComponents()
{
    return &m_components;
}

std::vector<bool>* Manager::GetComponentsStatus()
{
    return &m_activeComponents;
}

bool Manager::DoComponents()
{
    for (int i = 0; i < m_components.size(); i++)
    {
        if (m_activeComponents[i])
        {
            m_components[i]->DoTechnique();
        }
    }
    return true;
}