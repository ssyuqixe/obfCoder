#ifndef JUNKER_H
#define JUNKER_H

#include "Functions.h"
#include "Component.h"
#include "Parser.h"
#include <iostream>
#include <string>
#include <vector>

class Junker : public Component
{

private:
	std::vector<std::wstring> *p_ContentFile = nullptr;
	std::vector<Variable> *p_Variables = nullptr;
	Parser *p_Parser = nullptr;
	std::string m_tag = "Junker";
	// todo: rename variables
	std::vector<std::wstring> m_allJunkNames;
	int amountOfVariables;
	int amountOfJunk;

	bool FindIndexToAddJunk(int &index, int diffrence, Variable *&variable);
	std::vector<indexPair> FindBlockedIndexForJunk();
	void UpdateBlockedIndexs(int index, int change, std::vector<indexPair> &contBlockedSpace);
	void AddJunk(int &index, Variable *&variable, std::wstring oper, std::vector<indexPair> &contBlockedSpace);
	void AddJunkInc(int &index, Variable *&variable, std::vector<indexPair> &contBlockedSpace);
	void AddForConnected(int &index, Variable *&variable, std::vector<indexPair> &contBlockedSpace);
	void AddForSemiConnected(int &index, Variable *&variable, std::vector<indexPair> &contBlockedSpace);
	void AddForUnconnected(int &index, std::vector<indexPair> &contBlockedSpace);
	void InsertJunkToCode(std::vector<std::wstring> &junkCode, int &index, std::vector<indexPair> &contBlockedSpace);

public:
	Junker(std::vector<std::wstring> *p_ContentFile, Parser *p_Parser) : p_ContentFile(p_ContentFile), p_Parser(p_Parser)
	{
		if (p_Parser != nullptr)
			p_Variables = p_Parser->GetVariables();
		m_allJunkNames.push_back(L"do");
		m_allJunkNames.push_back(L"or");
		m_allJunkNames.push_back(L"if");
	}

	void FindJunkPlace(int amountOfVariables, int amountOfJunk);
	// temporary solution
	bool SetVariables(std::vector<Variable> *variables)
	{
		p_Variables = variables;
		return true;
	}

	bool Update(std::vector<int> &settings) override;
	bool DoTechnique() override;
	std::string GetTag() override { return m_tag; };
	void SetTag(std::string tag) override { this->m_tag = tag; };
};

#endif // JUNKER_H