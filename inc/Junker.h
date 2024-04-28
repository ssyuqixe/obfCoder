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
	std::string m_Tag = "Junker";

	std::vector<std::wstring> m_AllJunkNames;
	int m_HowManyVariables = 0;
	int m_HowManyJunkTechniques = 0;
	std::vector<std::wstring> m_JunkCode;
	std::vector<indexPair> m_ImmutableLocations;

	int RandomIndexForJunk(int &size);
	bool FindIndexToAddJunk(int &index, int diffrence, Variable *&p_VariableData);
	std::vector<indexPair> FindBlockedIndexesForJunk();
	int FindJunkPlace(Variable *&p_VariableData);
	void UpdateBlockedIndexes(int index, int change);

	void AddJunk(int &index, Variable *&p_VariableData, std::wstring arithmeticOperation);
	void AddJunkInc(int &index, Variable *&p_VariableData);
	void AddForLoop(int &index, Variable *&p_VariableData, int type);
	void AddJunkCode(int &index, Variable *&p_VariableData);
	void InsertJunkToCode(int &index);


public:
	Junker(std::vector<std::wstring> *p_ContentFile, Parser *p_Parser) : p_ContentFile(p_ContentFile), p_Parser(p_Parser)
	{
		if (p_Parser != nullptr)
			p_Variables = p_Parser->GetVariables();
	}

	bool Update(std::vector<int> &settings) override;
	bool DoTechnique() override;
	std::string GetTag() override { return m_Tag; };
	void SetTag(std::string tag) override { this->m_Tag = tag; };
};

#endif // JUNKER_H