#include "Junker.h"
#include "Functions.h"
#include "Settings.h"
#include <iostream>
#include <sstream>
#include <fstream>
#include <random>
#include <codecvt>


void Junker::FindJunkPlace(int amountOfVariables, int amountOfJunk)
{
	srand(time(NULL));
	int _amountOfVariables = 0;
	while (_amountOfVariables < amountOfVariables && ptr_variables->size() > specialVariables) {
		int size = ptr_mainString->size();
		int index = rand() % size;
		bool isVariable = false;
		int diffrence = 1;
		Variable* variableData = nullptr;
		std::vector<indexPair> contBlokedSpace = FindBlockedIndexForJunk();



		unsigned char isIndexBlocked = 0;
		bool downIndexBlocked = false;
		bool upIndexBlocked = false;


		for (auto const& pair : contBlokedSpace) {
			if (index >= pair.first || index <= pair.second) {
				isIndexBlocked = 1;
				break;
			}

		}
		if (isIndexBlocked == 0)
			for (auto const& variable : *ptr_variables)
				isVariable = FindIndexToAddJunk(index, 0, variableData);

		while (isVariable == false)
		{
			downIndexBlocked = false;
			upIndexBlocked = false;

			for (auto const& pair : contBlokedSpace) {
				int plusindex = index + diffrence;
				int minusindex = index - diffrence;
				if (plusindex < size && (plusindex >= pair.first && plusindex <= pair.second)) {
					upIndexBlocked = true;
				}

				if (minusindex >= 0 && (minusindex >= pair.first && minusindex <= pair.second)) {
					downIndexBlocked = true;
				}

			}

			if (upIndexBlocked == false)
				isVariable = FindIndexToAddJunk(index, diffrence, variableData);

			if (isVariable == false && downIndexBlocked == false)
				isVariable = FindIndexToAddJunk(index, -diffrence, variableData);

			diffrence++;
			if (diffrence > size)
				throw "Not found variables";
		}
		//std::sort(settings::junkerOptions.begin(), settings::junkerOptions.end());
		int option;

		for (int i = 0; i < amountOfJunk; i++) {
			option = settings::junkerOptions[(rand() % settings::junkerOptions.size())];
			switch (option - 1) {
			case 0:
				AddJunk(index, variableData, L"+=", contBlokedSpace);
				break;
			case 1:
				AddJunk(index, variableData, L"-=", contBlokedSpace);
				break;
			case 2:
				AddJunk(index, variableData, L"*=", contBlokedSpace);
				break;
			case 3:
				AddForConnected(index, variableData, contBlokedSpace);
				break;
			case 4:
				AddForSemiConnected(index, variableData, contBlokedSpace);
				break;
			case 5:
				AddForUnconnected(index, contBlokedSpace);
				break;
			case 6:
				AddJunkInc(index, variableData, contBlokedSpace);
				break;

			}
		}
		_amountOfVariables++;
	}
}

bool Junker::FindIndexToAddJunk(int& index, int diffrence, Variable*& variableData)
{
	std::vector<std::wstring> contToCheckIfPointer;

	if (index + diffrence >= ptr_mainString->size() || index + diffrence < 0)
		return false;

	for (auto& variable : *ptr_variables) {
		if (!ptr_mainString->at(index + diffrence).empty() && ptr_mainString->at(index + diffrence).find(L" " + variable.name + L" ") != std::wstring::npos) {

			int helpindex = -1;
			Split(ptr_mainString->at(index + diffrence), contToCheckIfPointer, L' ');
			for (int i = 0; i < contToCheckIfPointer.size(); i++) {
				if (contToCheckIfPointer[i].compare(variable.name) == 0) {
					helpindex = i;
					break;
				}
			}

			if ((helpindex - 1) >= 0 && (contToCheckIfPointer[helpindex - 1].compare(L"->") == 0 || variable.isPointer > 0 || contToCheckIfPointer[helpindex - 1].compare(L".") == 0) || contToCheckIfPointer[helpindex - 1].compare(L"]") == 0)
				continue;

			//if ((helpindex + 1) < contToCheckIfPointer.size() && contToCheckIfPointer[helpindex + 1].compare(L"[") == 0) // [0][0]
			if (variable.isArray > 0 || variable.type.compare(L"bool") == 0)
				continue;

			if (ptr_mainString->at(index + diffrence).find(L" const ") != std::wstring::npos && ptr_mainString->at(index + diffrence).find(L"const ") != std::wstring::npos)
				continue;

			//if ((helpindex + 2) < contToCheckIfPointer.size() && contToCheckIfPointer[helpindex + 2].compare(L"new") == 0)
			//	continue;

			index += diffrence;
			variableData = &variable;
			return true;
		}
	}
	return false;
}



std::vector<indexPair> Junker::FindBlockedIndexForJunk()
{
	std::vector<indexPair> contBlokedSpace;
	int countOfRange = 0;
	int indexStart = -1;
	bool isInRange = false;
	int sumCountOfRange = 0;
	for (int i = 0; i < ptr_mainString->size(); i++) {
		if (!ptr_mainString->at(i).empty() && countOfRange == 0 && ((ptr_mainString->at(i).find(L"class") != std::wstring::npos) || (ptr_mainString->at(i).find(L"struct") != std::wstring::npos)))
		{
			indexStart = i;
			isInRange = true;

		}

		sumCountOfRange = CountOfRangeChars(i, *ptr_mainString);
		countOfRange += sumCountOfRange;

		if (isInRange && sumCountOfRange < 0 && countOfRange == 0) {
			isInRange = false;
			contBlokedSpace.push_back(indexPair(indexStart, i));
			indexStart = -1;
		}



	}


	return contBlokedSpace;
}


void Junker::UpdateBlockedIndexs(int index, int change, std::vector<indexPair>& contBlokedSpace)
{
	for (auto& pair : contBlokedSpace) {
		if (index < pair.first)
		{
			pair.first += change;
			pair.second += change;
		}
	}

}

void Junker::AddJunk(int& index, Variable*& variable, std::wstring oper, std::vector<indexPair>& contBlokedSpace)
{
	//std::wstring randomName = randomUnicode(7, 0x0041, 0x005A);
	wchar_t random = (rand() % 9) + 49 ;
	std::wstring junk = L"\t " + variable->name + L" " + oper + L" " + random + L";\n\0";

	if (index + 1 < ptr_mainString->size() && ptr_mainString->at(index + 1).find(L"{") != std::wstring::npos)
		index++;


	if (oper.compare(L"*=") == 0) oper = L"/=";
	else if (oper.compare(L"/=") == 0) oper = L"*=";
	else if (oper.compare(L"+=") == 0) oper = L"-=";
	else if (oper.compare(L"-=") == 0) oper = L"+=";


	std::wstring junk2 = L"\t " + variable->name + L" " + oper + L" " + random + L";\n\0";

	ptr_mainString->insert(ptr_mainString->begin() + index + 1, junk);
	ptr_mainString->insert(ptr_mainString->begin() + index + 2, junk2);

	UpdateBlockedIndexs(index, 2, contBlokedSpace);
	index += 1; //+

}

void Junker::AddJunkInc(int& index, Variable*& variable, std::vector<indexPair>& contBlokedSpace)
{
	std::wstring junk1 = L"\t " + variable->name + L" ++ ;\n\0";
	std::wstring junk2 = L"\t " + variable->name + L" -- ;\n\0";
	int countOfAdd = (rand() % 20) + 1;

	if (index + 1 < ptr_mainString->size() && ptr_mainString->at(index + 1).find(L"{") != std::wstring::npos)
		index++;

	for (int i = 0; i < countOfAdd; i++) {
		ptr_mainString->insert(ptr_mainString->begin() + index + 1, junk1);
		ptr_mainString->insert(ptr_mainString->begin() + index + 2, junk2);
		index += 1;
	}
	UpdateBlockedIndexs(index, countOfAdd, contBlokedSpace);
	index += countOfAdd;
}


void Junker::AddForConnected(int& index, Variable*& variable, std::vector<indexPair>& contBlokedSpace)
{

	wchar_t random = (rand() % 10) + 48;
	std::wstring uniname = RandomUnicodeUntilNewValue(5, 0x0061, 0x007A, allJunkNames);
	while (uniname.compare(L"or") == 0 || uniname.compare(L"do") == 0) {
		uniname = RandomUnicodeUntilNewValue(5, 0x0061, 0x007A, allJunkNames); // RandomUnicode(2, 0x4E00, 0x62FF);
	}
	allJunkNames.push_back(uniname);

	std::wstring junk = L" \n\t int " + uniname + L" ; \n\t for( " + uniname + L" = 0; " + uniname + L" < " + random + L"; " + uniname + L" ++) { \n \0";
	std::wstring junk2 = L"\t " + variable->name + L" ++; }\n\0";
	std::wstring junk3 = L"\t " + variable->name + L" -= " + random + L";\n\0";

	if (index + 1 < ptr_mainString->size() && ptr_mainString->at(index + 1).find(L"{") != std::wstring::npos)
		index++;



	ptr_mainString->insert(ptr_mainString->begin() + index + 1, junk);
	ptr_mainString->insert(ptr_mainString->begin() + index + 2, junk2);
	ptr_mainString->insert(ptr_mainString->begin() + index + 3, junk3);

	UpdateBlockedIndexs(index, 3, contBlokedSpace);
	index += 3;

}


void Junker::AddForSemiConnected(int& index, Variable*& variable, std::vector<indexPair>& contBlokedSpace)
{

	wchar_t random = (rand() % 10) + 48;
	std::wstring uniname = RandomUnicodeUntilNewValue(5, 0x0061, 0x007A, allJunkNames);
	while (uniname.compare(L"or") == 0 || uniname.compare(L"do") == 0) {
		uniname = RandomUnicodeUntilNewValue(5, 0x0061, 0x007A, allJunkNames); // RandomUnicode(2, 0x4E00, 0x62FF);
	}
	allJunkNames.push_back(uniname);
	std::wstring addvariable1 = RandomUnicode(5, 0x0061, 0x007A); // RandomUnicode(2, 0x4E00, 0x62FF);
	std::wstring addvariable2 = RandomUnicode(5, 0x0061, 0x007A);// RandomUnicode(2, 0x4E00, 0x62FF);
	std::wstring junk = L" \n\t int " + addvariable1 + L" = 0; \n";
	std::wstring junk2 = L"\t bool " + addvariable2 + L" = true; \n";
	std::wstring junk3 = L"\t int " + uniname + L" ; \n\t for( " + uniname + L" = 0; " + uniname + L" < " + random + L"; " + uniname + L" ++) {\n";
	std::wstring junk4 = L"\t " + addvariable1 + L" += (int) " + variable->name + L" ;\n";
	std::wstring junk5 = L"\t if( " + addvariable1 + L" ) " + addvariable2 + L" = false; \n } \n";

	if (index + 1 < ptr_mainString->size() && ptr_mainString->at(index + 1).find(L"{") != std::wstring::npos)
		index++;


	ptr_mainString->insert(ptr_mainString->begin() + index + 1, junk);
	ptr_mainString->insert(ptr_mainString->begin() + index + 2, junk2);
	ptr_mainString->insert(ptr_mainString->begin() + index + 3, junk3);
	ptr_mainString->insert(ptr_mainString->begin() + index + 4, junk4);
	ptr_mainString->insert(ptr_mainString->begin() + index + 5, junk5);
	UpdateBlockedIndexs(index, 5, contBlokedSpace);
	index += 5;
}


void Junker::AddForUnconnected(int& index, std::vector<indexPair>& contBlokedSpace)
{
	wchar_t random = (rand() % 10) + 48;
	std::wstring uniname = RandomUnicodeUntilNewValue(5, 0x0061, 0x007A, allJunkNames);
	while (uniname.compare(L"or") == 0 || uniname.compare(L"do") == 0) {
		uniname = RandomUnicodeUntilNewValue(5, 0x0061, 0x007A, allJunkNames); // RandomUnicode(2, 0x4E00, 0x62FF);
	}
	allJunkNames.push_back(uniname);

	std::wstring addvariable1 = RandomUnicode(5, 0x0061, 0x007A); // RandomUnicode(2, 0x4E00, 0x62FF);
	std::wstring addvariable2 = RandomUnicode(5, 0x0061, 0x007A); // RandomUnicode(2, 0x4E00, 0x62FF);
	std::wstring junk = L" \n \t int " + addvariable1 + L" = 0; \n\0";
	std::wstring junk2 = L"\t int " + addvariable2 + L" = 1; \n\0";
	std::wstring junk3 = L"\t int " + uniname + L" ; \n\t for( " + uniname + L" = 0; " + uniname + L" < " + random + L"; " + uniname + L" ++) {\n\0";
	std::wstring junk4 = L"\t " + addvariable1 + L" *= " + addvariable2 + L" ;\n\0";
	std::wstring junk5 = L"\t switch( " + addvariable1 + L" )  { \n case 0: " + addvariable2 + L" = 0; \n break; \n case 1: " + addvariable2 + L" = 1; \n break;\n case 3: " + addvariable2 + L" = 3; \n break; \n case 7: " + addvariable2 + L" = 7; \n break; \n case 10: " + addvariable2 + L" = 10; \n break; \n default: " + addvariable2 + L" = 14; \n break; }\n }\n\0";

	if (index + 1 < ptr_mainString->size() && ptr_mainString->at(index + 1).find(L"{") != std::wstring::npos)
		index++;


	ptr_mainString->insert(ptr_mainString->begin() + index + 1, junk);
	ptr_mainString->insert(ptr_mainString->begin() + index + 2, junk2);
	ptr_mainString->insert(ptr_mainString->begin() + index + 3, junk3);
	ptr_mainString->insert(ptr_mainString->begin() + index + 4, junk4);
	ptr_mainString->insert(ptr_mainString->begin() + index + 5, junk5);
	UpdateBlockedIndexs(index, 5, contBlokedSpace);
	index += 5;

}