#ifndef JUNKER_H
#define JUNKER_H

#include "Functions.h"
#include <iostream>
#include <string>
#include <vector>

class Junker
{

private:
	std::vector<std::wstring>* ptr_mainString;
	std::vector<Variable>* ptr_variables;
	std::vector<std::wstring> allJunkNames;

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
	Junker(std::vector<std::wstring>* mainString, std::vector<Variable>* variables) : ptr_mainString(mainString), ptr_variables(variables) {
		allJunkNames.push_back(L"do");
		allJunkNames.push_back(L"or");
		allJunkNames.push_back(L"if");
	}
	void FindJunkPlace(int amountOfVariables, int amountOfJunk);

};

#endif // JUNKER_H