#ifndef RENAMER_H
#define RENAMER_H
#include "Component.h"
#include "Functions.h"
#include <iostream>
#include <string>
#include <vector>

class Renamer : public Component
{
    std::vector<std::wstring> *p_ContentFile;
	std::vector<Variable> *p_Variables;

    //todo: delete it later
    bool IsContinue(std::vector<indexPair> indexPosition, bool isContinue);

public:
    Renamer(std::vector<std::wstring> *mainString) : p_ContentFile(mainString) {}

    //temporary solution
    bool SetVariables(std::vector<Variable> *variables) { p_Variables = variables; return true; }

    bool Update(std::vector<int> &settings) override;
    bool DoTechnique() override;

};


#endif // RENAMER_H