#ifndef MANAGER_H
#define MANAGER_H

#include "Component.h"
#include <iostream>
#include <vector>
#include <string>

class Manager
{
    std::vector<Component*> m_components;
    std::vector<bool> m_activeComponents;
public:
    Manager();
    ~Manager();	

    void AddComponent(Component* component, bool active);
    void StateComponent(Component* component, bool state);
    void StateComponent(std::string tag, bool state);
    void RemoveComponent(Component* component);

    Component* GetComponent(std::string tag);
    bool GetComponentState(std::string tag);
    std::vector<Component*>* GetComponents();
    std::vector<bool>* GetComponentsStatus();
    void DefaultSetup(std::vector<std::wstring>* p_ContentFile);

    bool DoComponents();

};




#endif // MANAGER_H