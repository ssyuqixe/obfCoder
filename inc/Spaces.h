#ifndef SPACES_H
#define SPACES_H
#include "Component.h"
#include <iostream>
#include <string>
#include <vector>

class Spaces : public Component
{
    std::vector<std::wstring> *p_ContentFile;

public:
    Spaces(std::vector<std::wstring> *mainString) : p_ContentFile(mainString) {}

    bool Update(std::vector<int> &settings) override;
    bool DoTechnique() override;
};


#endif // SPACES_H