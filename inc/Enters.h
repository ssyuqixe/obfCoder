#ifndef ENTERS_H
#define ENTERS_H
#include "Component.h"
#include "Functions.h"
#include <iostream>
#include <string>
#include <vector>

class Enters : public Component
{
    std::vector<std::wstring> *p_ContentFile;
    std::string tag = "Enters";

    //todo: delete it later
    bool IsContinue(std::vector<indexPair> indexPosition, bool isContinue);
    std::vector<indexPair> FindCharIndex(std::wstring &line, std::wstring _char, bool isContinue);
    void OperatorException(std::wstring &line, std::wstring findOperator, std::wstring changeOperator, short replace, short find, std::vector<indexPair> &indexPositions);


public:
    Enters(std::vector<std::wstring> *mainString) : p_ContentFile(mainString) {}

    bool Update(std::vector<int> &settings) override;
    bool DoTechnique() override;
    std::string GetTag() override { return tag; };
    void SetTag(std::string tag) override { this->tag = tag;};
};

#endif // ENTERS_H