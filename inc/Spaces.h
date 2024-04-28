#ifndef SPACES_H
#define SPACES_H
#include "Component.h"
#include "Functions.h"
#include <iostream>
#include <string>
#include <vector>

class Spaces : public Component
{
    std::vector<std::wstring> *p_ContentFile;

    //todo: delete it later
    bool IsContinue(std::vector<indexPair> indexPosition, bool isContinue);
    void OperatorException(std::wstring &line, std::wstring findOperator, std::wstring changeOperator, short replace, short find, std::vector<indexPair> &indexPositions);
    std::vector<indexPair> FindCharIndex(std::wstring &line, std::wstring _char, bool isContinue);
    
	std::vector<std::wstring> special_operators{ L"+=", L"-=", L"*=", L"/=", L"<=",L">=",L"++", L"--", L"!=", L"//", L"<<", L">>", L"**", L"->", L"||" };
	std::vector<std::wstring> operators{ L"=",L"+", L"-", L"/", L"*", L"%", L"&", L"<", L">", L"^", L"!", L"?", L",", L"." }; 

public:
    Spaces(std::vector<std::wstring> *mainString) : p_ContentFile(mainString) {}

    bool Update(std::vector<int> &settings) override;
    bool DoTechnique() override;
};


#endif // SPACES_H