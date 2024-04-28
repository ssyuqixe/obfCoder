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
	// change later the random engine
	srand(time(NULL));
	int _amountOfVariables = 0;
	while (_amountOfVariables < amountOfVariables && p_Variables->size() > specialVariables)
	{
		int size = (int)(p_ContentFile->size());
		int index = randomEngine.gen() % size;
		bool isVariable = false;
		int diffrence = 1;
		Variable *variableData = nullptr;
		std::vector<indexPair> contBlockedSpace = FindBlockedIndexForJunk();

		unsigned char isIndexBlocked = 0;
		bool downIndexBlocked = false;
		bool upIndexBlocked = false;

		for (auto const &pair : contBlockedSpace)
			if (index >= pair.first || index <= pair.second)
			{
				isIndexBlocked = 1;
				break;
			}
		if (isIndexBlocked == 0)
			for (auto const &variable : *p_Variables)
				isVariable = FindIndexToAddJunk(index, 0, variableData);

		while (isVariable == false)
		{
			downIndexBlocked = false;
			upIndexBlocked = false;

			for (auto const &pair : contBlockedSpace)
			{
				int plusindex = index + diffrence;
				int minusindex = index - diffrence;
				if (plusindex < size && (plusindex >= pair.first && plusindex <= pair.second))
				{
					upIndexBlocked = true;
				}

				if (minusindex >= 0 && (minusindex >= pair.first && minusindex <= pair.second))
				{
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
		// std::sort(settings::junkerOptions.begin(), settings::junkerOptions.end());
		int option = -1;

		bool isAllFalse = true;
		for (const auto &option : settings::junkerOptions)
			if (option == true)
			{
				isAllFalse = false;
				break;
			}

		if (!isAllFalse)
			for (int i = 0; i < amountOfJunk; i++)
			{
				option = -1;

				while (option == -1)
				{
					option = randomEngine.gen() % settings::junkerOptions.size();
					if (settings::junkerOptions[option] == false)
						option = -1;
				}
				switch (option)
				{
				case 0:
					AddJunk(index, variableData, L"+=", contBlockedSpace);
					break;
				case 1:
					AddJunk(index, variableData, L"-=", contBlockedSpace);
					break;
				case 2:
					AddJunk(index, variableData, L"*=", contBlockedSpace);
					break;
				case 3:
					AddForConnected(index, variableData, contBlockedSpace);
					break;
				case 4:
					AddForSemiConnected(index, variableData, contBlockedSpace);
					break;
				case 5:
					AddForUnconnected(index, contBlockedSpace);
					break;
				case 6:
					AddJunkInc(index, variableData, contBlockedSpace);
					break;
				default:
					break;
				}
			}
		_amountOfVariables++;
	}
}

bool Junker::FindIndexToAddJunk(int &index, int diffrence, Variable *&variableData)
{
	std::vector<std::wstring> contToCheckIfPointer;

	if (index + diffrence >= p_ContentFile->size() || index + diffrence < 0)
		return false;

	for (auto &variable : *p_Variables)
	{
		if (!p_ContentFile->at(index + diffrence).empty() && p_ContentFile->at(index + diffrence).find(L" " + variable.name + L" ") != std::wstring::npos)
		{

			int helpindex = -1;
			Split(p_ContentFile->at(index + diffrence), contToCheckIfPointer, L' ');
			for (int i = 0; i < contToCheckIfPointer.size(); i++)
			{
				if (contToCheckIfPointer[i].compare(variable.name) == 0)
				{
					helpindex = i;
					break;
				}
			}

			if ((helpindex - 1) >= 0 && (contToCheckIfPointer[helpindex - 1].compare(L"->") == 0 || variable.isPointer > 0 || contToCheckIfPointer[helpindex - 1].compare(L".") == 0) || contToCheckIfPointer[helpindex - 1].compare(L"]") == 0)
				continue;

			// if ((helpindex + 1) < contToCheckIfPointer.size() && contToCheckIfPointer[helpindex + 1].compare(L"[") == 0) // [0][0]
			if (variable.isArray > 0 || variable.type.compare(L"bool") == 0)
				continue;

			if (p_ContentFile->at(index + diffrence).find(L" const ") != std::wstring::npos && p_ContentFile->at(index + diffrence).find(L"const ") != std::wstring::npos)
				continue;

			// if ((helpindex + 2) < contToCheckIfPointer.size() && contToCheckIfPointer[helpindex + 2].compare(L"new") == 0)
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
	std::vector<indexPair> contBlockedSpace;
	int countOfRange = 0;
	int indexStart = -1;
	bool isInRange = false;
	int sumCountOfRange = 0;
	for (int i = 0; i < p_ContentFile->size(); i++)
	{
		if (!p_ContentFile->at(i).empty() && countOfRange == 0 && ((p_ContentFile->at(i).find(L"class") != std::wstring::npos) || (p_ContentFile->at(i).find(L"struct") != std::wstring::npos)))
		{
			indexStart = i;
			isInRange = true;
		}

		sumCountOfRange = CountOfRangeChars((*p_ContentFile)[i]);
		countOfRange += sumCountOfRange;

		if (isInRange && sumCountOfRange < 0 && countOfRange == 0)
		{
			isInRange = false;
			contBlockedSpace.push_back(indexPair(indexStart, i));
			indexStart = -1;
		}
	}

	return contBlockedSpace;
}

void Junker::UpdateBlockedIndexs(int index, int change, std::vector<indexPair> &contBlockedSpace)
{
	for (auto &pair : contBlockedSpace)
		if (index < pair.first)
		{
			pair.first += change;
			pair.second += change;
		}
}

void Junker::AddJunk(int &index, Variable *&variable, std::wstring oper, std::vector<indexPair> &contBlockedSpace)
{
	// std::wstring randomName = randomUnicode(7, 0x0041, 0x005A);
	wchar_t random = (randomEngine.gen() % 9) + 49;
	std::wstring junk = L"\t " + variable->name + L" " + oper + L" " + random + L";\n\0";

	if (index + 1 < p_ContentFile->size() && p_ContentFile->at(index + 1).find(L"{") != std::wstring::npos)
		index++;

	if (oper.compare(L"*=") == 0)
		oper = L"/=";
	else if (oper.compare(L"/=") == 0)
		oper = L"*=";
	else if (oper.compare(L"+=") == 0)
		oper = L"-=";
	else if (oper.compare(L"-=") == 0)
		oper = L"+=";

	std::wstring junk2 = L"\t " + variable->name + L" " + oper + L" " + random + L";\n\0";

	p_ContentFile->insert(p_ContentFile->begin() + index + 1, junk);
	p_ContentFile->insert(p_ContentFile->begin() + index + 2, junk2);

	UpdateBlockedIndexs(index, 2, contBlockedSpace);
	index += 1; //+
}

void Junker::AddJunkInc(int &index, Variable *&variable, std::vector<indexPair> &contBlockedSpace)
{
	std::wstring junk1 = L"\t " + variable->name + L" ++ ;\n\0";
	std::wstring junk2 = L"\t " + variable->name + L" -- ;\n\0";
	int countOfAdd = (randomEngine.gen() % 20) + 1;

	if (index + 1 < p_ContentFile->size() && p_ContentFile->at(index + 1).find(L"{") != std::wstring::npos)
		index++;

	for (int i = 0; i < countOfAdd; i++)
	{
		p_ContentFile->insert(p_ContentFile->begin() + index + 1, junk1);
		p_ContentFile->insert(p_ContentFile->begin() + index + 2, junk2);
		index += 1;
	}
	UpdateBlockedIndexs(index, countOfAdd, contBlockedSpace);
	index += countOfAdd;
}

void Junker::AddForConnected(int &index, Variable *&variable, std::vector<indexPair> &contBlockedSpace)
{

	wchar_t random = (randomEngine.gen() % 10) + 48;
	std::wstring uniname = RandomUnicodeUntilNewValue(5, 0x0061, 0x007A, allJunkNames);
	while (uniname.compare(L"or") == 0 || uniname.compare(L"do") == 0)
	{
		uniname = RandomUnicodeUntilNewValue(5, 0x0061, 0x007A, allJunkNames); // RandomUnicode(2, 0x4E00, 0x62FF);
	}
	allJunkNames.push_back(uniname);

	std::vector<std::wstring> junkCode;
	junkCode.push_back(L" \n\t int " + uniname + L" ; \n\t for( " + uniname + L" = 0; " + uniname + L" < " + random + L"; " + uniname + L" ++) { \n \0");
	junkCode.push_back(L"\t " + variable->name + L" ++; }\n\0");
	junkCode.push_back(L"\t " + variable->name + L" -= " + random + L";\n\0");

	InsertJunkToCode(junkCode, index, contBlockedSpace);
}

void Junker::AddForSemiConnected(int &index, Variable *&variable, std::vector<indexPair> &contBlockedSpace)
{

	wchar_t random = (randomEngine.gen() % 10) + 48;
	std::wstring uniname = RandomUnicodeUntilNewValue(5, 0x0061, 0x007A, allJunkNames);
	while (uniname.compare(L"or") == 0 || uniname.compare(L"do") == 0)
	{
		uniname = RandomUnicodeUntilNewValue(5, 0x0061, 0x007A, allJunkNames); // RandomUnicode(2, 0x4E00, 0x62FF);
	}
	allJunkNames.push_back(uniname);
	std::wstring addvariable1 = RandomUnicode(5, 0x0061, 0x007A); // RandomUnicode(2, 0x4E00, 0x62FF);
	std::wstring addvariable2 = RandomUnicode(5, 0x0061, 0x007A); // RandomUnicode(2, 0x4E00, 0x62FF);
	std::vector<std::wstring> junkCode;
	junkCode.push_back(L" \n\t int " + addvariable1 + L" = 0; \n");
	junkCode.push_back(L"\t bool " + addvariable2 + L" = true; \n");
	junkCode.push_back(L"\t int " + uniname + L" ; \n\t for( " + uniname + L" = 0; " + uniname + L" < " + random + L"; " + uniname + L" ++) {\n");
	junkCode.push_back(L"\t " + addvariable1 + L" += (int) " + variable->name + L" ;\n");
	junkCode.push_back(L"\t if( " + addvariable1 + L" ) " + addvariable2 + L" = false; \n } \n");

	InsertJunkToCode(junkCode, index, contBlockedSpace);
}

void Junker::AddForUnconnected(int &index, std::vector<indexPair> &contBlockedSpace)
{
	wchar_t random = (randomEngine.gen() % 10) + 48;
	std::wstring uniname = RandomUnicodeUntilNewValue(5, 0x0061, 0x007A, allJunkNames);
	while (uniname.compare(L"or") == 0 || uniname.compare(L"do") == 0)
	{
		uniname = RandomUnicodeUntilNewValue(5, 0x0061, 0x007A, allJunkNames); // RandomUnicode(2, 0x4E00, 0x62FF);
	}
	allJunkNames.push_back(uniname);

	std::wstring addvariable1 = RandomUnicode(5, 0x0061, 0x007A); // RandomUnicode(2, 0x4E00, 0x62FF);
	std::wstring addvariable2 = RandomUnicode(5, 0x0061, 0x007A); // RandomUnicode(2, 0x4E00, 0x62FF);

	// change later junk to better word
	// also find better way to paste templates (e.g ''' ''' like python or load from file)
	std::vector<std::wstring> junkCode;
	junkCode.push_back(L" \n \t int " + addvariable1 + L" = 0; \n\0");
	junkCode.push_back(L"\t int " + addvariable2 + L" = 1; \n\0");
	junkCode.push_back(L"\t int " + uniname + L" ; \n\t for( " + uniname + L" = 0; " + uniname + L" < " + random + L"; " + uniname + L" ++) {\n\0");
	junkCode.push_back(L"\t " + addvariable1 + L" *= " + addvariable2 + L" ;\n\0");
	junkCode.push_back(L"\t switch( " + addvariable1 + L" )  { \n case 0: " + addvariable2 + L" = 0; \n break; \n case 1: " + addvariable2 + L" = 1; \n break;\n case 3: " + addvariable2 + L" = 3; \n break; \n case 7: " + addvariable2 + L" = 7; \n break; \n case 10: " + addvariable2 + L" = 10; \n break; \n default: " + addvariable2 + L" = 14; \n break; }\n }\n\0");

	InsertJunkToCode(junkCode, index, contBlockedSpace);
}

void Junker::InsertJunkToCode(std::vector<std::wstring> &junkCode, int &index, std::vector<indexPair> &contBlockedSpace)
{
	if (index + 1 < p_ContentFile->size() && p_ContentFile->at(index + 1).find(L"{") != std::wstring::npos)
		index++;

	for (auto i = 0; i < junkCode.size(); i++)
		p_ContentFile->insert(p_ContentFile->begin() + index + i + 1, junkCode[i]);
	UpdateBlockedIndexs(index, (int)junkCode.size(), contBlockedSpace);
	index += (int)junkCode.size();
}

bool Junker::Update(std::vector<int> &settings)
{
	if(settings.size() == 1)
		p_Parser->FindVariables();
	else if (settings.size() == 2)
	{
		amountOfVariables = settings[0];
		amountOfJunk = settings[1];
		return true;
	}

	return false;
}

bool Junker::DoTechnique()
{
	FindJunkPlace(amountOfVariables, amountOfJunk);
	return true;
}