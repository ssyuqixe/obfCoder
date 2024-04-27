#ifndef RENAMER_H
#define RENAMER_H
#include "Component.h"
#include <iostream>
#include <string>
#include <vector>

class Renamer : public Component
{
    std::vector<std::wstring> *p_ContentFile;

public:
    Renamer(std::vector<std::wstring> *mainString) : p_ContentFile(mainString) {}

    bool Update(std::vector<int> &settings) override;
    bool DoTechnique() override;
};


#endif // RENAMER_H