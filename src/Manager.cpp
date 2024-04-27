#include "Manager.h"


Manager::Manager()
{
}

void Manager::AddComponent(Components* component, bool active=true)
{
    components.push_back(component);
    activeComponents.push_back(active);
}

void Manager::StateComponent(Components* component, bool state)
{
    for (int i = 0; i < components.size(); i++)
    {
        if (components[i] == component)
        {
            components[i]->SetActive(state);
        }
    }
}

void Manager::RemoveComponent(Components* component)
{
    for(int i = 0; i < components.size(); i++)
    {
        if (components[i] == component)
        {
            components.erase(components.begin() + i);
            activeComponents.erase(activeComponents.begin() + i);
            break;
        }
    }

}

std::vector<Components*>* Manager::GetComponents()
{
    return &components;
}

bool Manager::DoComponents()
{
    for (int i = 0; i < m_components.size(); i++)
    {
        if (m_activeComponents[i])
        {
            components[i]->DoTechnique();
        }
    }
    return true;
}