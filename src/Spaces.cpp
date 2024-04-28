#include "Spaces.h"
#include "Functions.h"
#include <iostream>
#include <vector>
#include <string>

bool Spaces::IsContinue(std::vector<indexPair> indexPosition, bool isContinue)
{
	if (!indexPosition.empty())
		isContinue = (indexPosition.back().second >= INT32_MAX) ? true : false;
	return isContinue;
}

bool Spaces::Update(std::vector<int> &settings)
{
    return true;
}

bool Spaces::DoTechnique()
{
	bool isContinue = false;
	std::vector<indexPair> indexPositions;

	for (auto &line : *p_ContentFile)
	{

		indexPositions.erase(indexPositions.begin(), indexPositions.end());
		indexPositions = FindCharIndex(line, L"\"", isContinue);
		isContinue = IsContinue(indexPositions, isContinue);

		// OperatorException(line, L" ' ", L"'", 2, -2, indexPositions);
		OperatorException(line, L" ; ", L";", 2, -2, indexPositions);
		OperatorException(line, L" , ", L",", 3, -2, indexPositions);
		OperatorException(line, L" ( ", L"(", 2, -2, indexPositions);
		OperatorException(line, L" [ ", L"[", 2, -2, indexPositions);
		OperatorException(line, L" { ", L"{", 2, -2, indexPositions);
		OperatorException(line, L" ) ", L")", 2, -2, indexPositions);
		OperatorException(line, L" ] ", L"]", 2, -2, indexPositions);
		OperatorException(line, L" } ", L"}", 2, -2, indexPositions);

		OperatorException(line, L"( ", L"(", 2, -1, indexPositions);
		OperatorException(line, L"[ ", L"[", 2, -1, indexPositions);
		OperatorException(line, L"{ ", L"{", 2, -1, indexPositions);
		OperatorException(line, L" )", L")", 2, -1, indexPositions);
		OperatorException(line, L" ]", L"]", 2, -1, indexPositions);
		OperatorException(line, L" }", L"}", 2, -1, indexPositions);
		// OperatorException(line, L"' ", L"'", 2, -1, indexPositions);
		// OperatorException(line, L" '", L"'", 2, -1, indexPositions);

		for (auto &o : special_operators)
			OperatorException(line, L" " + o + L" ", o, 4, -2, indexPositions);

		for (auto &o : operators)
			OperatorException(line, L" " + o + L" ", o, 3, -2, indexPositions);

		OperatorException(line, L"\t", L"", 1, -1, indexPositions);
		// OperatorException(line, L", ", L",", 2, -1, indexPositions);
		OperatorException(line, L" ,", L",", 2, -1, indexPositions);
		OperatorException(line, L"; ", L";", 2, -1, indexPositions);
		OperatorException(line, L" ;", L";", 2, -1, indexPositions);
	}
    return true;
}


std::vector<indexPair> Spaces::FindCharIndex(std::wstring &line, std::wstring _char, bool isContinue)
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


void Spaces::OperatorException(std::wstring &line, std::wstring findOperator, std::wstring changeOperator, short replace, short find, std::vector<indexPair> &indexPositions)
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