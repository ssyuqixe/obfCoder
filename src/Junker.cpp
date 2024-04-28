#include "Junker.h"
#include "Functions.h"
#include "Settings.h"
#include <iostream>
#include <vector>
#include <string>

int Junker::RandomIndexForJunk(int &size)
{
	int index = 0;
	bool isIndexBlocked = false;
	unsigned char nonStuckCounter = 0;
	do
	{
		isIndexBlocked = false;
		index = randomEngine.gen() % size;
		for (auto const &pair : m_ImmutableLocations)
			if (index >= pair.first || index <= pair.second)
			{
				isIndexBlocked = true;
				break;
			}
		if (nonStuckCounter++ > 100)
			return -1;
	} while (isIndexBlocked == true);

	return index;
}

bool Junker::FindIndexToAddJunk(int &index, int diffrence, Variable *&p_VariableData)
{

	if (index + diffrence >= p_ContentFile->size() || index + diffrence < 0)
		return false;

	std::vector<std::wstring> splittedLine;

	for (auto &variable : *p_Variables)
	{
		if (!p_ContentFile->at(index + diffrence).empty() && p_ContentFile->at(index + diffrence).find(L" " + variable.name + L" ") != std::wstring::npos)
		{

			int i_Variable = 0;
			Split(p_ContentFile->at(index + diffrence), splittedLine, L' ');

			while (splittedLine[i_Variable].compare(variable.name) != 0)
			{
				i_Variable++;
			}

			// exclude pointers and arrays from junking
			if ((i_Variable - 1) >= 0 && (variable.isPointer > 0 || splittedLine[i_Variable - 1].compare(L"->") == 0 || splittedLine[i_Variable - 1].compare(L".") == 0) || splittedLine[i_Variable - 1].compare(L"]") == 0)
				continue;
			// exclude arrays and bool from junking
			if (variable.isArray > 0 || variable.type.compare(L"bool") == 0)
				continue;
			// exclude const variables from junking
			if (p_ContentFile->at(index + diffrence).find(L" const ") != std::wstring::npos && p_ContentFile->at(index + diffrence).find(L"const ") != std::wstring::npos)
				continue;

			index += diffrence;
			p_VariableData = &variable;
			return true;
		}
	}
	return false;
}

std::vector<indexPair> Junker::FindBlockedIndexesForJunk()
{
	m_ImmutableLocations.clear();
	int countOfRange = 0;
	int i_Start = -1;
	bool isInRange = false;
	int sumCountOfRange = 0;
	for (int i_Line = 0; i_Line < p_ContentFile->size(); i_Line++)
	{
		if (!p_ContentFile->at(i_Line).empty() && countOfRange == 0 && ((p_ContentFile->at(i_Line).find(L"class") != std::wstring::npos) || (p_ContentFile->at(i_Line).find(L"struct") != std::wstring::npos)))
		{
			i_Start = i_Line;
			isInRange = true;
		}

		sumCountOfRange = CountOfRangeChars((*p_ContentFile)[i_Line]);
		countOfRange += sumCountOfRange;

		// i assume that, parser will be deleted cases like "class" and 2-3 new lines then "{"
		if (i_Start != i_Line && isInRange == true && sumCountOfRange == 0 && countOfRange == 0)
		{
			m_ImmutableLocations.push_back(indexPair(i_Start, i_Line));
			isInRange = false;
		}
	}

	return m_ImmutableLocations;
}

int Junker::FindJunkPlace(Variable *&p_VariableData)
{
	if (p_Variables->size() <= specialVariables)
		return -1;

	int size = int(p_ContentFile->size());
	m_ImmutableLocations = FindBlockedIndexesForJunk();
	int index = RandomIndexForJunk(size);

	bool isVariable = false;
	bool downIndexBlocked = false;
	bool upIndexBlocked = false;
	int diffrence = 0;
	int upIndex = index;
	int downIndex = index;
	do
	{
		downIndexBlocked = false;
		upIndexBlocked = false;
		upIndex = index + diffrence;
		downIndex = index - diffrence;

		if (upIndex >= size && downIndex < 0)
			return -1;

		for (auto const &pair : m_ImmutableLocations)
		{
			if (upIndex < size && (upIndex >= pair.first && upIndex <= pair.second))
			{
				upIndexBlocked = true;
			}

			if (downIndex >= 0 && (downIndex >= pair.first && downIndex <= pair.second))
			{
				downIndexBlocked = true;
			}

			if (upIndexBlocked == true && downIndexBlocked == true)
				break;
		}

		if (upIndexBlocked == false && upIndex < size)
			isVariable = FindIndexToAddJunk(index, diffrence, p_VariableData);

		if (isVariable == false && downIndexBlocked == false && downIndex >= 0)
			isVariable = FindIndexToAddJunk(index, -diffrence, p_VariableData);

		diffrence++;
	} while (isVariable == false);
	return index;
}

void Junker::UpdateBlockedIndexes(int index, int change)
{
	for (auto &pair : m_ImmutableLocations)
	{
		if (index < pair.first)
		{
			pair.first += change;
			pair.second += change;
		}
		else
			return;
	}
}

void Junker::AddJunk(int &index, Variable *&p_VariableData, std::wstring arithmeticOperation)
{
	wchar_t randomNumber = (randomEngine.gen() % 9) + 49;

	std::wstring firstArthmeticExpression = L"\t " + p_VariableData->name + L" " + arithmeticOperation + L" " + randomNumber + L";\n\0";
	if (arithmeticOperation.compare(L"*=") == 0)
		arithmeticOperation = L"/=";
	else if (arithmeticOperation.compare(L"/=") == 0)
		arithmeticOperation = L"*=";
	else if (arithmeticOperation.compare(L"+=") == 0)
		arithmeticOperation = L"-=";
	else if (arithmeticOperation.compare(L"-=") == 0)
		arithmeticOperation = L"+=";

	m_JunkCode.clear();
	m_JunkCode.insert(m_JunkCode.begin(),
					  {firstArthmeticExpression,
					   {L"\t " + p_VariableData->name + L" " + arithmeticOperation + L" " + randomNumber + L";\n\0"}});
	InsertJunkToCode(index);
}

void Junker::AddJunkInc(int &index, Variable *&p_VariableData)
{
	unsigned char countOfAdd = unsigned char((randomEngine.gen() % 25) + 5);

	m_JunkCode.clear();
	for (unsigned char i = 0; i < countOfAdd; i++)
	{
		m_JunkCode.insert(m_JunkCode.begin(),
						  {{L"\t " + p_VariableData->name + L" ++ ;\n\0"},
						   {L"\t " + p_VariableData->name + L" -- ;\n\0"}});
	}
	InsertJunkToCode(index);
}

void Junker::AddForLoop(int &index, Variable *&p_VariableData, int type)
{
	if (type < 1 || type > 3)
		return;

	wchar_t randomNumber = (randomEngine.gen() % 10) + 48;

	std::wstring uniname = RandomUnicodeUntilNewValue(5, 0x0061, 0x007A, m_AllJunkNames);
	m_AllJunkNames.push_back(uniname);

	std::wstring firstJunkVariable = RandomUnicode(5, 0x0061, 0x007A);
	std::wstring secondJunkVariable = RandomUnicode(5, 0x0061, 0x007A);
	while (firstJunkVariable.compare(secondJunkVariable) == 0)
		secondJunkVariable = RandomUnicode(5, 0x0061, 0x007A);

	switch (type)
	{
	case 1:
		m_JunkCode.clear();
		m_JunkCode.insert(m_JunkCode.begin(),
						  {{L" \n\t int " + uniname + L" ; \n\t for( " + uniname + L" = 0; " + uniname + L" < " + randomNumber + L"; " + uniname + L" ++) { \n \0"},
						   {L"\t " + p_VariableData->name + L" ++; }\n\0"},
						   {L"\t " + p_VariableData->name + L" -= " + randomNumber + L";\n\0"}});

		break;
	case 2:
		m_JunkCode.clear();
		m_JunkCode.insert(m_JunkCode.begin(),
						  {{L" \n\t int " + firstJunkVariable + L" = 0; \n"},
						   {L"\t bool " + secondJunkVariable + L" = true; \n"},
						   {L"\t int " + uniname + L" ; \n\t for( " + uniname + L" = 0; " + uniname + L" < " + randomNumber + L"; " + uniname + L" ++) {\n"},
						   {L"\t " + firstJunkVariable + L" += (int) " + p_VariableData->name + L" ;\n"},
						   {L"\t if( " + firstJunkVariable + L" ) " + secondJunkVariable + L" = false; \n } \n"}});
		break;
	case 3:
		m_JunkCode.clear();
		m_JunkCode.insert(m_JunkCode.begin(),
						  {{L" \n \t int " + firstJunkVariable + L" = 0; \n\0"},
						   {L"\t int " + secondJunkVariable + L" = 1; \n\0"},
						   {L"\t int " + uniname + L" ; \n\t for( " + uniname + L" = 0; " + uniname + L" < " + randomNumber + L"; " + uniname + L" ++) {\n\0"},
						   {L"\t " + firstJunkVariable + L" *= " + secondJunkVariable + L" ;\n\0"},
						   {L"\t switch( " + firstJunkVariable + L" )  { \n case 0: " + secondJunkVariable + L" = 0; \n break; \n case 1: " + secondJunkVariable + L" = 1; \n break;\n case 3: " + secondJunkVariable + L" = 3; \n break; \n case 7: " + secondJunkVariable + L" = 7; \n break; \n case 10: " + secondJunkVariable + L" = 10; \n break; \n default: " + secondJunkVariable + L" = 14; \n break; }\n }\n\0"}});

		break;
	default:
		return;
	}

	InsertJunkToCode(index);
}

void Junker::AddJunkCode(int &index, Variable *&p_VariableData)
{
	int techniquesCounter = 0;
	while (techniquesCounter < m_HowManyJunkTechniques)
	{
		// check if there is any option selected
		bool isAllFalse = true;
		for (const auto &option : settings::junkerOptions)
			if (option == true)
			{
				isAllFalse = false;
				break;
			}

		if (isAllFalse == true)
			return;

		int option = 0;
		for (int i = 0; i < m_HowManyJunkTechniques; i++)
		{

			// random option from selected
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
				AddJunk(index, p_VariableData, L"+=");
				break;
			case 1:
				AddJunk(index, p_VariableData, L"-=");
				break;
			case 2:
				AddJunk(index, p_VariableData, L"*=");
				break;
			case 3:
				AddForLoop(index, p_VariableData, 1);
				break;
			case 4:
				AddForLoop(index, p_VariableData, 2);
				break;
			case 5:
				AddForLoop(index, p_VariableData, 3);
				break;
			case 6:
				AddJunkInc(index, p_VariableData);
				break;
			default:
				break;
			}
		}
		techniquesCounter++;
	}
}

void Junker::InsertJunkToCode(int &index)
{
	if (m_JunkCode.size() == 0)
		return;

	for (auto i = 0; i < m_JunkCode.size(); i++)
		p_ContentFile->insert(p_ContentFile->begin() + index + i + 1, m_JunkCode[i]);
	UpdateBlockedIndexes(index, int(m_JunkCode.size()));
	index += (int)m_JunkCode.size();
}

bool Junker::Update(std::vector<int> &settings)
{
	if (settings.size() == 2)
	{
		m_HowManyVariables = settings[0];
		m_HowManyJunkTechniques = settings[1];
		return true;
	}
	return false;
}

bool Junker::DoTechnique()
{
	int variableCounter = 0;
	int index = 0;
	m_ImmutableLocations.clear();
	Variable *p_VariableData = nullptr;
	while (variableCounter < m_HowManyVariables)
	{
		p_VariableData = nullptr;
		index = FindJunkPlace(p_VariableData);
		if (index == -1 || p_VariableData == nullptr)
			return false;
		AddJunkCode(index, p_VariableData);
		variableCounter++;
	}

	return true;
}