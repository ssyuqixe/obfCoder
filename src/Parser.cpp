#include "Parser.h"
#include <map>
#include <ctime>
#include <codecvt>
#include <random>
#include "Encryption.h"
#include "Junker.h"
#include "FileHandling.h"

static std::mt19937_64 random;

bool Parser::IsContinue(std::vector<indexPair> indexPosition, bool isContinue)
{
	if (!indexPosition.empty())
		isContinue = (indexPosition.back().second >= INT32_MAX) ? true : false;
	return isContinue;
}

Parser::Parser(std::vector<std::wstring>* ptrContentFile)
{
	this->mainString = ptrContentFile;

	AddExpectionsWords();
}

Parser::Parser(FileHandling& file, std::string name)
{
	this->mainString = file.LoadFile(name);

	AddExpectionsWords();
}

void Parser::SpaceOperators()
{
	std::vector<std::wstring> sufix{L"=", L"+", L"-", L"*", L"/", L"<", L">", L"&", L"|", L"^", L"!"};
	std::vector<int> positions;
	std::vector<indexPair> indexPositions;
	std::vector<indexPair> indexPositionsBlock;
	size_t index = 0;
	size_t indexOfPair = 0;

	bool isChange = true;
	bool isContinue = false;
	bool isNotInRange;

	for (auto &line : *this->mainString)
	{
		if (CheckInclude(line))
			continue;

		indexPositions.erase(indexPositions.begin(), indexPositions.end());
		indexPositions = FindCharIndex(line, L"\"", isContinue);

		isContinue = IsContinue(indexPositions, isContinue);

		for (auto &o : special_operators)
			OperatorException(line, o, L" " + o + L" ", 2, 2, indexPositions);

		// Exception for (, [, ), ]
		OperatorException(line, L";", L" ; ", 1, 2, indexPositions);
		OperatorException(line, L"\t", L" \t ", 1, 2, indexPositions);
		OperatorException(line, L"(", L"( ", 1, 1, indexPositions);
		OperatorException(line, L"[", L" [ ", 1, 2, indexPositions);
		OperatorException(line, L")", L" )", 1, 1, indexPositions);
		OperatorException(line, L"]", L" ] ", 1, 2, indexPositions);
		// !!

		for (const auto &op : operators)
		{
			isChange = true;

			if (!line.empty() && line.find(op) != std::string::npos)
			{
				index = line.find(op);

				while (line.find(op, index) != std::string::npos)
				{
					isChange = true;
					isNotInRange = true;
					indexOfPair = 0;

					for (size_t i = 0; i < indexPositions.size(); i++)
					{
						if (indexPositions[i].first < index && index < indexPositions[i].second)
						{
							isNotInRange = false;
							indexOfPair = i;
							break;
						}
					}

					if (isNotInRange == true)
					{
						for (auto &c : sufix) // Check if there is a double operator
							if ((index - 1 >= 0 && index + 1 < line.length()) && (line[index + 1] == c[0] || line[index - 1] == c[0]))
								isChange = false;
						if (op.compare(L".") == 0)
						{ // Check if number is float
							if (index - 1 >= 0)
							{
								std::vector<std::wstring> container;
								Split(line.substr(0, line.find(op, index) + 1), container, L' ');
								if (container.empty() == false && isdigit(container.back()[0]))
								{
									isChange = false;
								}
							}
						}

						if (isChange)
						{
							line.replace(index, 1, L" " + op + L" ");
							index = line.find(op, index + 2);

							if (!indexPositions.empty())
							{

								for (size_t i = indexOfPair + 1; i < indexPositions.size(); i++)
								{
									indexPositions[i].first += 2;
									indexPositions[i].second += 2;
								}
							}
						}
						else
							index = line.find(op, index + 1);
					}
					else if (index + 1 < line.length())
						index = line.find(op, index + 1);
					else
						break;
				}
			}
		}

		DeleteDoubleSpaces(line);
	}
	FindVariables();
}

// Add space after search variable names e.g. for a constructor
void Parser::SpaceOperatorsFix()
{
	std::vector<indexPair> indexPositions;
	bool isContinue = false;

	for (auto &line : *this->mainString)
	{

		if (CheckInclude(line))
			continue;

		indexPositions.erase(indexPositions.begin(), indexPositions.end());

		indexPositions = FindCharIndex(line, L"\"", isContinue);

		isContinue = IsContinue(indexPositions, isContinue);

		OperatorException(line, L";", L" ; ", 1, 2, indexPositions);
		// OperatorException(line, L"'", L" ' ", 1, 2, indexPositions);
		OperatorException(line, L",", L" , ", 1, 2, indexPositions);
		OperatorException(line, L"(", L" ( ", 1, 2, indexPositions);
		OperatorException(line, L"[", L" [ ", 1, 2, indexPositions);
		OperatorException(line, L"{", L" { ", 1, 2, indexPositions);
		OperatorException(line, L")", L" ) ", 1, 2, indexPositions);
		OperatorException(line, L"]", L" ] ", 1, 2, indexPositions);
		OperatorException(line, L"}", L" } ", 1, 2, indexPositions);

		DeleteDoubleSpaces(line);
	}
}

void Parser::FindVariables()
{

	std::vector<std::wstring> typesOfVariables{L"int", L"double", L"float", L"string", L"uint8_t", L"uint16_t", L"uint32_t", L"uint64_t", L"int8_t", L"int16_t", L"int32_t", L"int64_t", L"char", L"char16_t", L"char32_t", L"bool", L"short", L"wchar_t", L"size_t"}; // L"void"

	bool save = false;
	bool next = false;
	bool change = false;
	std::wstring typeOfVariable;
	size_t iter = 0;
	int pointerCounter = 0;
	int arrayDimCounter = 0;

	for (auto &line : *this->mainString)
	{
		iter++;
		Split(line, this->splitedLine, L' ');

		if (!line.empty() && line.find(L"#include") != std::string::npos)
			continue;

		for (int i = 0; i < splitedLine.size(); i++)
		{

			next = false;
			if (!splitedLine[i].empty() && splitedLine[i].find(L'(') != std::string::npos)
			{ // Stop searching in line if there is a function by using "(" with name
				save = false;
				continue;
			}
			if (save && !splitedLine[i].empty() && splitedLine[i].find(L'&') != std::string::npos)
			{ // Stop searching in line if there is a function by using "(" with name
				next = true;
				continue;
			}
			if (save && !splitedLine[i].empty() && splitedLine[i].find(L'*') != std::string::npos)
			{
				next = true;

				if (splitedLine[i].find(L"**") != std::string::npos)
					pointerCounter += 2;
				else
					pointerCounter++;
				continue;
			}

			for (auto &type : typesOfVariables)
				if (!next && !line.empty() && line.find(type) != std::string::npos)
					if (splitedLine[i].compare(type) == 0)
					{				 // Checking if text is type of variable
						save = true; // set to save next word
						next = true; // set to check next word
						typeOfVariable = type;
						break;
					}
			if (save && !next)
			{
				save = false;

				change = true;
				if (splitedLine[i] == L">" || splitedLine[i] == L">>" || splitedLine[i] == L";" || splitedLine[i] == L"," || splitedLine[i] == L"const")
					change = false;

				///*
				if (i - 2 >= 0 && splitedLine[i - 2] == L"const")
				{
					change = false;
				} //*/

				if (change == true)
					for (auto &variable : variables)
					{
						if (variable.newName == splitedLine[i])
						{
							change = false;
							pointerCounter = 0;
							break;
						}
					}

				if (change == true)
				{
					arrayDimCounter = 0;
					/*
					if ((i + 2 < splitedLine.size()) && splitedLine[i + 2].compare(L"new") == 0) {

					}*/
					bool startedArray = false;
					if (i + 1 < splitedLine.size() && splitedLine[i + 1].compare(L"[") == 0)
					{
						startedArray = true;
						for (int u = i + 2; u < splitedLine.size(); u++)
						{
							if (startedArray && splitedLine[u].compare(L"]") == 0)
							{
								arrayDimCounter++;
								startedArray = false;
								if (u + 1 < splitedLine.size() && splitedLine[u + 1].compare(L"[") == 0)
								{
									startedArray = true;
									u++;
								}
							}
						}
					}

					NewNameVariables(variables, splitedLine[i], typeOfVariable, pointerCounter, arrayDimCounter);
				}
			}
		}
		this->splitedLine.erase(this->splitedLine.begin(), this->splitedLine.end());
	}
}

std::vector<indexPair> Parser::FindCharIndex(std::wstring &line, std::wstring _char, bool isContinue)
{
	std::vector<size_t> allIndexs;

	size_t startIndex;

	if (!line.empty() && line.find(_char) != std::wstring::npos)
	{
		startIndex = line.find(_char);
		if (startIndex - 1 >= 0 && line[startIndex - 1] != L'\\') //
			allIndexs.push_back(startIndex);

		while (line.find(_char, startIndex + 1) != std::wstring::npos && startIndex - 1 >= 0 && line[startIndex - 1] != L'\\')
		{
			startIndex = line.find(_char, startIndex + 1);
			allIndexs.push_back(startIndex);
		}
	}

	std::vector<indexPair> indexVector;

	if (!allIndexs.empty())
		if (isContinue)
		{
			indexVector.push_back(indexPair(0, allIndexs[0]));
			for (size_t i = 1; i < allIndexs.size() - 1; i += 2)
				indexVector.push_back(indexPair(allIndexs[i], allIndexs[i + 1]));

			if (!(allIndexs.size() % 2))
				indexVector.push_back(indexPair(allIndexs.back(), INT32_MAX));
		}
		else
		{
			for (size_t i = 0; i < allIndexs.size() - 1; i += 2)
				indexVector.push_back(indexPair(allIndexs[i], allIndexs[i + 1]));

			if (allIndexs.size() % 2)
				indexVector.push_back(indexPair(allIndexs.back(), INT32_MAX));
		}

	return indexVector;
}

std::vector<indexPair> Parser::FindBlockIndex()
{
	std::vector<indexPair> indexVector;
	bool isBlockStarted = false;
	size_t startIndex;

	int i = 0;
	for (auto &line : *this->mainString)
	{
		if (!line.empty() && line.find(startBlock) != std::wstring::npos)
		{
			isBlockStarted = true;
			startIndex = i++;
			continue;
		}

		if (!line.empty() && isBlockStarted == true && line.find(endBlock) != std::wstring::npos)
		{
			indexVector.push_back(indexPair(startIndex, i++));
			isBlockStarted = false;
			continue;
		}

		i++;
	}

	return indexVector;
}

void Parser::NewNameVariables(std::vector<Variable> &variables, std::wstring word, std::wstring typeOfVariable, int pointerCounter, int arrayDimCounter)
{
	// std::wstring newName = randomUnicode(10, 0x0041, 0x005A); //A-Z
	std::wstring newName = RandomUnicode(1, 0x4E00, 0x62FF); // chinese 0x62FF
	int i = 1;
	bool change = true;
	while (change)
	{
		change = false;

		for (auto &element : variables)
		{
			if (element.newName == newName)
			{
				newName = RandomUnicode(++i, 0x4E00, 0x62FF);
				change = true;
				break;
			}
		}
	}
	variables.push_back(Variable(word, newName, typeOfVariable, pointerCounter, arrayDimCounter));
	// mapVariables.insert(Pair(word, newName));
}

void Parser::ChangeVariables()
{
	throw new std::exception("Not implemented");
}

void Parser::OperatorException(std::wstring &line, std::wstring findOperator, std::wstring changeOperator, short replace, short find, std::vector<indexPair> &indexPositions)
{
	size_t index;
	int indexOfPair = 0;
	bool isNotInRange;
	bool isHaveToChangeIndex;
	if (!line.empty() && line.find(findOperator) != std::wstring::npos)
	{
		index = line.find(findOperator);
		while (line.find(findOperator, index) != std::wstring::npos)
		{
			isNotInRange = true;
			isHaveToChangeIndex = false;
			if (!indexPositions.empty())
				for (int i = 0; i < indexPositions.size(); i++)
				{
					if (indexPositions[i].first <= index && index <= indexPositions[i].second)
					{
						isNotInRange = false;
						indexOfPair = i;
						break;
					}

					if (index < indexPositions[i].first)
					{
						isHaveToChangeIndex = true;
					}
				}

			if (isNotInRange)
			{
				line.replace(index, replace, changeOperator);

				if (!indexPositions.empty() && isHaveToChangeIndex == true)
				{
					if (index < indexPositions[0].first)
						indexOfPair = -1;
					for (int i = indexOfPair + 1; i < indexPositions.size(); i++)
					{
						indexPositions[i].first += find;
						indexPositions[i].second += find;
					}
					if (indexOfPair == -1)
						indexOfPair = 0;
				}

				index = line.find(findOperator, index + find + 1);
			}
			else
				index = line.find(findOperator, index + 1);
		}
	}
}

void Parser::DeleteDoubleSpaces(std::wstring &line)
{
	while (!line.empty() && line.find(L"  ") != std::wstring::npos)
		line.replace(line.find(L"  "), 2, L" ");
}

void Parser::DeleteEnters()
{
	throw new std::exception("Not implemented");
}

void Parser::DeleteUnnecessarySpaces()
{
	throw new std::exception("Not implemented");
}

void Parser::AddExpectionsWords()
{
	// mapVariables.insert(Pair(L" operator ", L"operator"));
	// mapVariables.insert(Pair(L" NULL ", L"NULL"));
	// mapVariables.insert(Pair(L" [ ", L"["));

	variables.push_back(Variable(L" operator ", L"operator", L"special"));
	variables.push_back(Variable(L" NULL ", L"NULL", L"special"));
	variables.push_back(Variable(L" [ ", L"[", L"special"));
	// variables.push_back(Variable(L"false", L"0", L"special"));
	// variables.push_back(Variable(L"true", L"1", L"special"));
	// variables.insert(variables.begin(), Variable(word, newName, typeOfVariable));
}


//todo: delete later
void Parser::ChangeLoops()
{
 throw new std::exception("Not implemented");
}

bool Parser::Update(std::vector<int> &settings)
{
	return true;
}

bool Parser::DoTechnique()
{
	SpaceOperators();
	return true;
}