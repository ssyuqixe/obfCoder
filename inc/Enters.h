#ifndef ENTERS_H
#define ENTERS_H
#include "Component.h"
#include <iostream>
#include <string>
#include <vector>

class Enters : public Component
{
    std::vector<std::wstring> *p_ContentFile;

public:
    Enters(std::vector<std::wstring> *mainString) : p_ContentFile(mainString) {}

    bool Update(std::vector<int> &settings) override;
    bool DoTechnique() override;
};

#endif // ENTERS_H