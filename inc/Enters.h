#ifndef ENTERS_H
#define ENTERS_H
#include "Component.h"
#include "Functions.h"
#include "Parser.h"
#include <iostream>
#include <string>
#include <vector>

class Enters : public Component
{
    std::vector<std::wstring> *p_ContentFile;
    Parser *p_Parser = nullptr;
    std::string m_Tag = "Enters";

public:
    Enters(std::vector<std::wstring> *p_ContentFile, Parser *p_Parser) : p_ContentFile(p_ContentFile), p_Parser(p_Parser) {}

    bool Update(std::vector<int> &settings) override;
    bool DoTechnique() override;
    std::string GetTag() override { return m_Tag; };
    void SetTag(std::string tag) override { this->m_Tag = tag; };
};

#endif // ENTERS_H