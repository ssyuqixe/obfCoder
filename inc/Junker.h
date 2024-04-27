#ifndef JUNKER_H
#define JUNKER_H

#include "Functions.h"
#include "Component.h"
#include <iostream>
#include <string>
#include <vector>

class Junker : public Component
{

private:
	std::vector<std::wstring>* p_ContentFile;
	std::vector<Variable>* p_Variables;
	std::vector<std::wstring> allJunkNames;
	int amountOfVariables;
	int amountOfJunk;

	bool FindIndexToAddJunk(int& index, int diffrence, Variable*& variable);
	std::vector<indexPair> FindBlockedIndexForJunk();
	void UpdateBlockedIndexs(int index, int change, std::vector<indexPair>& contBlockedSpace);
	void AddJunk(int& index, Variable*& variable, std::wstring oper, std::vector<indexPair>& contBlockedSpace);
	void AddJunkInc(int& index, Variable*& variable, std::vector<indexPair>& contBlockedSpace);
	void AddForConnected(int& index, Variable*& variable, std::vector<indexPair>& contBlockedSpace);
	void AddForSemiConnected(int& index, Variable*& variable, std::vector<indexPair>& contBlockedSpace);
	void AddForUnconnected(int& index, std::vector<indexPair>& contBlockedSpace);
	void InsertJunkToCode(std::vector<std::wstring> &junkCode, int &index, std::vector<indexPair> &contBlockedSpace);
public:
	Junker(std::vector<std::wstring>* mainString, std::vector<Variable>* variables) : p_ContentFile(mainString), p_Variables(variables) {
		allJunkNames.push_back(L"do");
		allJunkNames.push_back(L"or");
		allJunkNames.push_back(L"if");
	}
	void FindJunkPlace(int amountOfVariables, int amountOfJunk);

	bool Update(std::vector<int> &settings) override;
	bool DoTechnique() override;

};

#endif // JUNKER_H