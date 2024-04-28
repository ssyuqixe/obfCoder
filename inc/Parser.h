#ifndef PARSER_H
#define PARSER_H
#include "Functions.h"
#include "FileHandling.h"
#include "Component.h"

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>

typedef std::pair<std::wstring, std::wstring> Pair;
typedef std::multimap<std::wstring, std::wstring> MapCode;

class Parser : public Component
{
private:
	std::vector<std::wstring>* mainString;
	std::vector<std::wstring> splitedLine;
    std::string tag = "Parser";
	std::vector<std::wstring> special_operators{ L"+=", L"-=", L"*=", L"/=", L"<=",L">=",L"++", L"--", L"!=", L"//", L"<<", L">>", L"**", L"->", L"||" };
	std::vector<std::wstring> operators{ L"=",L"+", L"-", L"/", L"*", L"%", L"&", L"<", L">", L"^", L"!", L"?", L",", L"." }; 

	std::wstring startBlock = L"#define obf_block_start";
	std::wstring endBlock = L"#define obf_block_end";

	std::vector<Variable> variables;
	bool IsContinue(std::vector<indexPair> indexPosition, bool isContinue);


	std::vector<indexPair> FindCharIndex(std::wstring& line, std::wstring _char, bool isContinue);
	std::vector<indexPair> FindBlockIndex();

	void NewNameVariables(std::vector<Variable>& variables, std::wstring word, std::wstring typeOfVariable, int pointerCounter, int arrayDimCounter);

	void AddExpectionsWords();

public:
	Parser(std::vector<std::wstring>* ptrContentFile);
	Parser(FileHandling& file, std::string name);
	void SpaceOperators();

	void SpaceOperatorsFix();

	void FindVariables();
	void ChangeVariables();
	void OperatorException(std::wstring& line, std::wstring findOperator, std::wstring changeOperator, short replace, short find, std::vector<indexPair>& indexPositions);


	void DeleteDoubleSpaces(std::wstring& line);
	void DeleteEnters(); 
	void DeleteUnnecessarySpaces();

	
	void ChangeLoops();

	//temporary solution
	std::vector<Variable>* GetVariables() { return &variables; }

	bool Update(std::vector<int> &settings) override;
	bool DoTechnique() override;
    std::string GetTag() override { return tag; };
    void SetTag(std::string tag) override { this->tag = tag;};

};

#endif // PARSER_H