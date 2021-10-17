#pragma once
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
	void UpdateBlockedIndexs(int index, int change, std::vector<indexPair>& contBlokedSpace);
	void AddJunk(int& index, Variable*& variable, std::wstring oper, std::vector<indexPair>& contBlokedSpace);
	void AddJunkInc(int& index, Variable*& variable, std::vector<indexPair>& contBlokedSpace);
	void AddForConnected(int& index, Variable*& variable, std::vector<indexPair>& contBlokedSpace);
	void AddForSemiConnected(int& index, Variable*& variable, std::vector<indexPair>& contBlokedSpace);
	void AddForUnconnected(int& index, std::vector<indexPair>& contBlokedSpace);
public:
	Junker(std::vector<std::wstring>* mainString, std::vector<Variable>* variables) : ptr_mainString(mainString), ptr_variables(variables) {
		allJunkNames.push_back(L"do");
		allJunkNames.push_back(L"or");
		allJunkNames.push_back(L"if");
	}
	void FindJunkPlace(int amountOfVariables, int amountOfJunk);

};

