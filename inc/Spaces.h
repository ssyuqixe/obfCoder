#ifndef SPACES_H
#define SPACES_H
#include "Component.h"
#include "Functions.h"
#include "Parser.h"
#include <iostream>
#include <string>
#include <vector>

class Spaces : public Component
{
    std::vector<std::wstring> *p_ContentFile;
    Parser *p_Parser = nullptr;
    std::string m_Tag = "Spaces";

public:
    Spaces(std::vector<std::wstring> *mainString, Parser* p_Parser) : p_ContentFile(mainString), p_Parser(p_Parser) {}

    bool Update(std::vector<int> &settings) override;
    bool DoTechnique() override;
    std::string GetTag() override { return m_Tag; };
    void SetTag(std::string tag) override { m_Tag = tag;};
};


#endif // SPACES_H