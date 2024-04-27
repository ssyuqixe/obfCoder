#ifndef MANAGER_H
#define MANAGER_H

#include "Components.h"
#include <vector>

class Manager
{
    std::vector<Components*> m_components;
    std::vector<bool> m_activeComponents;
public:
    Manager();

    void AddComponent(Components* component);
    void StateComponent(Components* component, bool state);
    void RemoveComponent(Components* component);
    std::vector<Components*>* GetComponents();

    bool DoComponents();

};




#endif // MANAGER_H