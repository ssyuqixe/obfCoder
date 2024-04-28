#ifndef RENAMER_H
#define RENAMER_H
#include "Component.h"
#include "Functions.h"
#include "Parser.h"
#include <iostream>
#include <string>
#include <vector>

class Renamer : public Component
{
    std::vector<std::wstring> *p_ContentFile = nullptr;
    std::vector<Variable> *p_Variables = nullptr;
    Parser *p_Parser = nullptr;
    std::string tag = "Renamer";

public:
    Renamer(std::vector<std::wstring> *p_ContentFile, Parser *p_Parser) : p_ContentFile(p_ContentFile), p_Parser(p_Parser)
    {
        if (p_Parser != nullptr)
            p_Variables = p_Parser->GetVariables();
    }

    // temporary solution
    bool SetVariables(std::vector<Variable> *variables)
    {
        p_Variables = variables;
        return true;
    }

    bool Update(std::vector<int> &settings) override;
    bool DoTechnique() override;
    std::string GetTag() override { return tag; };
    void SetTag(std::string tag) override { this->tag = tag; };
};

#endif // RENAMER_H