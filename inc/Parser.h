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
	std::vector<std::wstring>* p_ContentFile;
    std::string m_Tag = "Parser";

	std::wstring startBlock = L"#define obf_block_start";
	std::wstring endBlock = L"#define obf_block_end";

	std::vector<Variable> m_Variables;


	std::vector<indexPair> FindBlockIndex();

	void NewNameVariables(std::wstring word, std::wstring typeOfVariable, int pointerCounter, int arrayDimCounter);

	void AddExpectionsWords();

public:
	Parser(std::vector<std::wstring>* ptrContentFile);
	Parser(FileHandling& file, std::string name);
	void SpaceOperators();

	void SpaceOperatorsFix();

	void FindVariables();
	void OperatorException(std::wstring& line, std::wstring findOperator, std::wstring changeOperator, short replace, short find, std::vector<indexPair>& indexPositions);

	bool IsContinue(const std::vector<indexPair>& indexPosition, bool isContinue);

	void DeleteDoubleSpaces(std::wstring& line);
	

	//temporary solution
	std::vector<Variable>* GetVariables() { return &m_Variables; }

	bool Update(std::vector<int> &settings) override;
	bool DoTechnique() override;
    std::string GetTag() override { return m_Tag; };
    void SetTag(std::string tag) override { this->m_Tag = tag;};

};

#endif // PARSER_H