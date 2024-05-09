#include "Parser.h"
#include <map>
#include <ctime>
#include <codecvt>
#include <random>
#include "Encryption.h"
#include "Junker.h"
#include "FileHandling.h"
#include "Settings.h"

bool Parser::IsContinue(const std::vector<indexPair> &indexPosition, bool isContinue)
{
	if (!indexPosition.empty())
		isContinue = (indexPosition.back().second >= INT32_MAX) ? true : false;
	return isContinue;
}

Parser::Parser(std::vector<std::wstring> *p_ContentFile)
{
	this->p_ContentFile = p_ContentFile;
	AddExpectionsWords();
}

Parser::Parser(FileHandling &file, std::string name)
{
	this->p_ContentFile = file.LoadFile(name);
	AddExpectionsWords();
}

void Parser::SpaceOperators()
{
	std::vector<std::wstring> suffixes{L"=", L"+", L"-", L"*", L"/", L"<", L">", L"&", L"|", L"^", L"!"};
	std::vector<int> positions;
	std::vector<indexPair> indexPositions;
	std::vector<indexPair> indexPositionsBlock;
	size_t index = 0;
	size_t indexOfPair = 0;

	std::vector<std::vector<std::wstring>> operatorExceptions{{L";", L" ; "}, {L"\t", L" \t "}, {L"(", L"( "}, {L"[", L" [ "}, {L")", L" )"}, {L"]", L" ] "}, {L"{", L" { "}, {L"}", L" } "}};

	bool isChange = true;
	bool isContinue = false;
	bool isNotInRange = true;

	for (auto &line : *p_ContentFile)
	{
		if (CheckInclude(line))
			continue;

		indexPositions.erase(indexPositions.begin(), indexPositions.end());
		indexPositions = FindCharIndex(line, L"\"", isContinue);

		isContinue = IsContinue(indexPositions, isContinue);

		for (const auto &op : settings::special_operators)
			OperatorException(line, op, L" " + op + L" ", 2, 2, indexPositions);

		// Exception for (, [, ), ]
		for (const auto &op : operatorExceptions)
			OperatorException(line, op[0], op[1], 1, short(op[1].length() - 1), indexPositions);

		for (const auto &op : settings::operators)
		{
			
			index = line.find(op);
			if (index == std::string::npos)
				continue;
			
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
					for (const auto &sufix : suffixes) // Check if there is a double operator
						if ((index - 1 >= 0 && index + 1 < line.length()) && (line[index + 1] == sufix[0] || line[index - 1] == sufix[0]))
							isChange = false;

					if (isChange == true && op.compare(L".") == 0)
					{ // Check if number is float
						if (index - 1 >= 0)
						{
							std::vector<std::wstring> container;
							Split(line.substr(0, line.find(op, index) + 1), container, L' ');
							if (container.empty() == false && isdigit(container.back()[0]))
								isChange = false;
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

		DeleteDoubleSpaces(line);
	}
	FindVariables();
}

// Add space after search variable names e.g. for a constructor
void Parser::SpaceOperatorsFix()
{
	std::vector<indexPair> indexPositions;
	bool isContinue = false;

	std::vector<std::vector<std::wstring>> operatorExceptions{{L";", L" ; "}, {L",", L" , "}, {L"(", L"( "}, {L"[", L" [ "}, {L"{", L" { "}, {L")", L" )"}, {L"]", L" ] "}, {L"}", L" } "}};

	for (auto &line : *p_ContentFile)
	{

		if (CheckInclude(line))
			continue;

		indexPositions.erase(indexPositions.begin(), indexPositions.end());
		indexPositions = FindCharIndex(line, L"\"", isContinue);
		isContinue = IsContinue(indexPositions, isContinue);

		for (const auto &op : operatorExceptions)
			OperatorException(line, op[0], op[1], 1, 2, indexPositions);

		DeleteDoubleSpaces(line);
	}
}

void Parser::FindVariables()
{

	std::vector<std::wstring> typesOfVariables{L"int", L"double", L"float", L"string", L"uint8_t", L"uint16_t", L"uint32_t", L"uint64_t", L"int8_t", L"int16_t", L"int32_t", L"int64_t", L"char", L"char16_t", L"char32_t", L"bool", L"short", L"wchar_t", L"size_t"}; // L"void"
	std::vector<std::wstring> splitedLine;

	bool saveNextWord = false;
	bool checkNextWord = false;
	bool addVariable = false;
	std::wstring typeOfVariable;
	int pointerCounter = 0;
	int arrayDimCounter = 0;

	for (auto &line : *p_ContentFile)
	{
		if (line.empty())
			continue;
		if (line.find(L"#include") != std::string::npos)
			continue;

		Split(line, splitedLine, L' ');

		for (int i = 0; i < splitedLine.size(); i++)
		{
			if (splitedLine[i].empty())
				continue;
			
			if (splitedLine[i].find(L'(') != std::string::npos)
			{ // Stop searching in line if there is a function by using "(" with name
				saveNextWord = false;
				continue;
			}

			if (saveNextWord == true)
			{
				if (splitedLine[i].find(L'&') != std::string::npos)
					// Next word is a reference
					continue;

				else if (splitedLine[i].find(L'*') != std::string::npos)
				{ // Next word is a pointer
					// check level of pointer (parser split pointers to form of "** ** ** *" etc.)
					(splitedLine[i].find(L"**") != std::string::npos) ? pointerCounter += 2 : pointerCounter++;
					continue;
				}
			}

			checkNextWord = false;

			for (const auto &type : typesOfVariables)
				if (line.find(type) != std::string::npos && splitedLine[i].compare(type) == 0)
				{				 // Checking if text is type of variable
					saveNextWord = true; 
					checkNextWord = true; 
					typeOfVariable = type;
					break;
				}

			if (saveNextWord == true && checkNextWord == false)
			{
				saveNextWord = false;
				addVariable = true;
				if ((splitedLine[i] == L">" || splitedLine[i] == L">>" || splitedLine[i] == L";" || splitedLine[i] == L"," || splitedLine[i] == L"const") && (i - 2 >= 0 && splitedLine[i - 2] == L"const"))
				{
					addVariable = false;
					continue;
				}

				for (const auto &variable : m_Variables)
				{
					if (variable.newName.compare(splitedLine[i]) == 0)
					{
						addVariable = false;
						pointerCounter = 0;
						break;
					}
				}

				if (addVariable == true)
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
					NewNameVariables(splitedLine[i], typeOfVariable, pointerCounter, arrayDimCounter);
				}
			}
		}
		splitedLine.erase(splitedLine.begin(), splitedLine.end());
	}
}

std::vector<indexPair> Parser::FindBlockIndex()
{
	std::vector<indexPair> indexVector;
	bool isBlockStarted = false;
	size_t startIndex = 0;

	int i = 0;
	for (const auto &line : *p_ContentFile)
	{
		if (line.empty())
			continue;
		else if (line.find(startBlock) != std::wstring::npos)
		{
			isBlockStarted = true;
			startIndex = i;
		}
		else if (isBlockStarted == true && line.find(endBlock) != std::wstring::npos)
		{
			indexVector.push_back(indexPair(startIndex, i));
			isBlockStarted = false;
		}
		i++;
	}

	return indexVector;
}

void Parser::NewNameVariables(std::wstring word, std::wstring typeOfVariable, int pointerCounter, int arrayDimCounter)
{
	std::wstring newName;
	bool isExist = false;
	do
	{
		newName = RandomUnicode((randomEngine.gen() % 10) + 1, settings::rangeOfUnicode[0], settings::rangeOfUnicode[1]);
		isExist = true;
		for (const auto &element : m_Variables)
		{
			if (element.newName.compare(newName) == 0)
			{
				isExist = false;
				break;
			}
		}
	} while (!isExist);
	m_Variables.push_back(Variable(word, newName, typeOfVariable, pointerCounter, arrayDimCounter));
}

void Parser::OperatorException(std::wstring &line, std::wstring findOperator, std::wstring changeOperator, short replace, short find, std::vector<indexPair> &indexPositions)
{
	size_t index = 0;
	int indexOfPair = 0;
	bool isNotInRange = true;
	bool isHasToChangeIndex = false;
	if (!line.empty() && line.find(findOperator) != std::wstring::npos)
	{
		index = line.find(findOperator);
		while (line.find(findOperator, index) != std::wstring::npos)
		{
			isNotInRange = true;
			isHasToChangeIndex = false;
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
						isHasToChangeIndex = true;
						indexOfPair = i;
						break;
					}
				}

			if (isNotInRange)
			{
				line.replace(index, replace, changeOperator);


				//check later if this change works
				if (!indexPositions.empty() && isHasToChangeIndex == true)
				{
					for (int i = indexOfPair; i < indexPositions.size(); i++)
					{
						indexPositions[i].first += find;
						indexPositions[i].second += find;
					}
					
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
	auto find = line.find(L"  ");
	while (!line.empty() && find != std::wstring::npos)
	{
		line.replace(find, 2, L" ");
		find = line.find(L"  ");
	}
}

void Parser::AddExpectionsWords()
{
	m_Variables.push_back(Variable(L" operator ", L"operator", L"special"));
	m_Variables.push_back(Variable(L" NULL ", L"NULL", L"special"));
	m_Variables.push_back(Variable(L" [ ", L"[", L"special"));
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