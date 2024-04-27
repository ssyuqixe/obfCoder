#include "Looper.h"
#include "Functions.h"
#include <iostream>
#include <vector>
#include <string>

bool Looper::Update(std::vector<int> &settings)
{
    return true;
}

bool Looper::DoTechnique()
{
    int index = 0;
	while (index != -1)
	{
		index = ChangeLoop(index);
	}

	std::vector<indexPair> indexBlockPosition = FindBlockIndex();
	for (const auto &indexes : indexBlockPosition)
	{
		p_ContentFile->at(indexes.first).erase();
		p_ContentFile->at(indexes.second).erase();
	}

    return true;
}

std::vector<indexPair> Looper::FindBlockIndex()
{
	std::vector<indexPair> indexVector;
	bool isBlockStarted = false;
	size_t startIndex;

	int i = 0;
	for (auto &line : *p_ContentFile)
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

int Looper::ChangeLoop(int indexLoop)
{
	int indexOfLoop = FindForLoop(indexLoop);
	if (indexOfLoop == -1)
		return -1;
	int indexOfSecondLoop = 0;
	int loopLength = LengthOfLoop(indexOfLoop);
	int index = 0;
	std::vector<std::wstring> copyOfLoop(loopLength);

	std::vector<std::wstring> contSplitedBySemicolon;
	std::vector<std::wstring> contSplitedByLowlyChar;

	std::wstring nameOfVar1[2];
	std::wstring nameOfVar2[2];

	std::wstring nameOfVar2If;

	for (int i = 0; i < loopLength; i++)
		copyOfLoop[i].assign(p_ContentFile->at(i + indexOfLoop));

	GetVariablesFromFor(copyOfLoop[0], nameOfVar1, 1, L' ');
	for (int i = 1; i < loopLength; i++)
	{
		if (copyOfLoop[i].find(L"for") != std::string::npos)
		{
			GetVariablesFromFor(copyOfLoop[i], nameOfVar2, 1, L' ');
			indexOfSecondLoop = i;
			break;
		}
	}

	nameOfVar2If = nameOfVar2[1];

	if (GetNameForChangeLoop(copyOfLoop[0], copyOfLoop[indexOfSecondLoop], nameOfVar2If))
		return indexOfLoop + loopLength;

	// indexOfLoop + loopLength;

	copyOfLoop.erase(copyOfLoop.begin() + indexOfSecondLoop);

	std::wstring forMain = L"for( int t = 0 ; t < ( " + nameOfVar1[1] + L" * " + nameOfVar2[1] + L" ) ; t ++ )\n\0";
	copyOfLoop.front() = forMain;

	int diff;
	for (int i = 1; i < loopLength - 1; i++)
	{
		index = 0;
		diff = 0;
		while (true)
		{
			if (!copyOfLoop[i].empty() && copyOfLoop[i].find(L" " + nameOfVar1[0] + L" ", index) != std::string::npos)
			{
				index = (int)(copyOfLoop[i].find(L" " + nameOfVar1[0] + L" ", index));
				copyOfLoop[i].replace(index + 1, nameOfVar1[0].length(), L" ( t / " + nameOfVar2If + L" ) ");
				diff = (int)(nameOfVar2[1].length() - nameOfVar1[0].length());
				index++;
			}
			else
				break;
		}

		index = 0;
		diff = (int)(nameOfVar2[1].length() - nameOfVar2[0].length());
		while (true)
		{
			if (!copyOfLoop[i].empty() && copyOfLoop[i].find(L" " + nameOfVar2[0] + L" ", index) != std::string::npos)
			{
				index = (int)(copyOfLoop[i].find(L" " + nameOfVar2[0] + L" ", index));
				copyOfLoop[i].replace(index + 1, nameOfVar2[0].length(), L" ( t % " + nameOfVar2If + L" ) ");
				index++;
			}
			else
				break;
		}
	}

	int lengthOfSecondLoop = LengthOfSecondLoop(indexOfSecondLoop, copyOfLoop);
	RemoveBracketOfSecondLoop(indexOfSecondLoop, loopLength, copyOfLoop);

	// if

	bool isSomething = false;
	for (int i = 1; i < indexOfSecondLoop; i++)
	{
		if (!copyOfLoop[i].empty())
			for (auto &_char : copyOfLoop[i])
			{
				if (((_char >= 65) && (_char <= 90)) || ((_char >= 97) && (_char <= 122)))
				{
					isSomething = true;
					break;
				}
			}
		if (isSomething)
			break;
	}

	if (isSomething)
	{
		std::wstring ifwstring = L"\t if( t % ( " + nameOfVar2If + L" ) == 0 )\n\0";
		copyOfLoop.insert(copyOfLoop.begin() + 2, ifwstring);
		copyOfLoop.insert(copyOfLoop.begin() + 3, L"{\n\0");
		copyOfLoop.insert(copyOfLoop.begin() + indexOfSecondLoop + 2, L"}\n\0");
		indexOfSecondLoop += 3;
	}

	isSomething = false;
	for (int i = indexOfSecondLoop + lengthOfSecondLoop; i < copyOfLoop.size() - 1; i++)
	{
		if (!copyOfLoop[i].empty())
			for (auto &_char : copyOfLoop[i])
			{
				if (((_char >= 65) && (_char <= 90)) || ((_char >= 97) && (_char <= 122)))
				{
					isSomething = true;
					break;
				}
			}
		if (isSomething)
			break;
	}

	if (isSomething)
	{
		std::wstring ifwstring = L"\t if( t % ( " + nameOfVar2If + L" ) == 0 )\n\0";
		copyOfLoop.insert(copyOfLoop.begin() + indexOfSecondLoop + lengthOfSecondLoop, ifwstring);
		copyOfLoop.insert(copyOfLoop.begin() + indexOfSecondLoop + lengthOfSecondLoop + 1, L"{\n\0");
		copyOfLoop.insert(copyOfLoop.end() - 1, L"}\n\0");
	}

	// indexOfSecondLoop = i;

	p_ContentFile->erase(p_ContentFile->begin() + indexOfLoop, p_ContentFile->begin() + indexOfLoop + loopLength);
	p_ContentFile->insert(p_ContentFile->begin() + indexOfLoop, copyOfLoop.begin(), copyOfLoop.end());
	return (int)(indexOfLoop + copyOfLoop.size());
}


int Looper::FindForLoop(int startIndex)
{
	int index = -1;

	std::vector<indexPair> indexBlockPosition = FindBlockIndex();

	int countOfRange = 0;
	bool isSecondLoopInRange = false;

	for (int i = startIndex; i < this->p_ContentFile->size(); i++)
	{

		if (!indexBlockPosition.empty())
		{
			for (auto &indexes : indexBlockPosition)
			{
				if (i < indexes.first)
					break;

				if (i >= indexes.first && i <= indexes.second)
				{
					i = (int)(indexes.second + 1);
				}
			}
		}

		if (isSecondLoopInRange && !p_ContentFile->at(i).empty() && p_ContentFile->at(i).find(L"for") != std::wstring::npos && countOfRange == 1)
		{
			return index;
		}

		if (isSecondLoopInRange && !p_ContentFile->at(i).empty())
		{
			int pos = CountOfRangeChars(p_ContentFile->at(i));
			countOfRange += pos;

			if (pos < 0 && countOfRange == 0)
				isSecondLoopInRange = false;
		}

		if (!p_ContentFile->at(i).empty() && p_ContentFile->at(i).find(L" for ") != std::wstring::npos)
		{

			isSecondLoopInRange = true;
			countOfRange += CountOfRangeChars(p_ContentFile->at(i));
			index = i;
		}
	}
	return -1;
}

int Looper::LengthOfLoop(int startIndex)
{
	bool isStartedRange = false;
	int length = 0;
	int countOfRange = 0;
	int index = startIndex;

	//check
	while (true)
	{
		length++;
		if (isStartedRange == false && countOfRange == 0 && CountOfRangeChars(p_ContentFile->at(index)) > 0)
			isStartedRange = true;
		countOfRange += CountOfRangeChars(p_ContentFile->at(index));

		if (isStartedRange == true && countOfRange == 0)
			break;

		index++;
	}

	return length;
}
//check
int Looper::LengthOfSecondLoop(int startIndex, std::vector<std::wstring> wstringTab)
{
	int lengthOfSecondLoop = 0;
	int countOfSecondRange = 0;
	while (countOfSecondRange != 0)
	{
		lengthOfSecondLoop++;
		countOfSecondRange += CountOfRangeChars(wstringTab[startIndex]);
		startIndex++;
	}
	return (countOfSecondRange == 0) ? lengthOfSecondLoop : 0;
}

void Looper::GetVariablesFromFor(std::wstring lineFor, std::wstring *tab, short index, wchar_t _char)
{
	std::vector<std::wstring> contSplitedBySemicolon;
	std::vector<std::wstring> contSplitedByLowlyChar;

	Split(lineFor, contSplitedBySemicolon, L';');
	Split(contSplitedBySemicolon[1], contSplitedByLowlyChar, _char);
	tab[0] = contSplitedByLowlyChar[1];
	tab[1] = contSplitedByLowlyChar[3];

	contSplitedBySemicolon.erase(contSplitedBySemicolon.begin(), contSplitedBySemicolon.end());
	contSplitedByLowlyChar.erase(contSplitedByLowlyChar.begin(), contSplitedByLowlyChar.end());
}

int Looper::GetNameForChangeLoop(std::wstring lineLoop, std::wstring lineLoopSecond, std::wstring &nameOfVar)
{

	std::vector<std::wstring> contSplitedBySemicolon;
	std::vector<std::wstring> contSplitedByLowlyChar;

	Split(lineLoop, contSplitedBySemicolon, L';');
	Split(contSplitedBySemicolon[2], contSplitedByLowlyChar, L' ');
	if (contSplitedByLowlyChar.size() == 5) // i += 5
	{
		if (contSplitedByLowlyChar[2].compare(L"+=") != 0 && contSplitedByLowlyChar[2].compare(L"++") != 0)
			return 1;

		if (contSplitedByLowlyChar[2].compare(L"++") == 0)
			contSplitedByLowlyChar[3] = L"1";
		nameOfVar = L" ( " + nameOfVar + L" * " + contSplitedByLowlyChar[3] + L" ) ";
	}
	else if (contSplitedByLowlyChar.size() == 7)
	{ // i = i + 5;
		if (contSplitedByLowlyChar[4].compare(L"+") != 0)
			return 1;

		if (contSplitedByLowlyChar[5].empty())
			contSplitedByLowlyChar[5] = L"1";
		nameOfVar = L" ( " + nameOfVar + L" * " + contSplitedByLowlyChar[5] + L" ) ";
	}

	contSplitedByLowlyChar.erase(contSplitedByLowlyChar.begin(), contSplitedByLowlyChar.end());

	Split(contSplitedBySemicolon[0], contSplitedByLowlyChar, L'=');

	while (contSplitedByLowlyChar[1].find(L' ') != std::string::npos)
	{
		contSplitedByLowlyChar[1].erase(contSplitedByLowlyChar[1].find(L' '), 1);
	}
	if (contSplitedByLowlyChar[1].compare(L"0") != 0)
		return 1;

	contSplitedBySemicolon.erase(contSplitedBySemicolon.begin(), contSplitedBySemicolon.end());
	contSplitedByLowlyChar.erase(contSplitedByLowlyChar.begin(), contSplitedByLowlyChar.end());

	Split(lineLoopSecond, contSplitedBySemicolon, L';');
	Split(contSplitedBySemicolon[0], contSplitedByLowlyChar, L'=');

	while (contSplitedByLowlyChar[1].find(L' ') != std::string::npos)
	{
		contSplitedByLowlyChar[1].erase(contSplitedByLowlyChar[1].find(L' '), 1);
	}
	if (contSplitedByLowlyChar[1].compare(L"0") != 0)
		return 1;
	return 0;
}

void Looper::RemoveBracketOfSecondLoop(int startIndex, int loopLength, std::vector<std::wstring> &wstringTab)
{
	int countOfRange = 0;
	for (int i = startIndex; i < loopLength - 1; i++)
	{ // 1
		int cOR = CountOfRangeChars(wstringTab[i]);
		countOfRange += cOR;
		if (cOR > 0 && countOfRange == 1) //>0
			wstringTab[i].replace(wstringTab[i].find(L'{'), 1, L" ");
		else if (cOR < 0 && countOfRange == 0) //>= 0
			wstringTab[i].replace(wstringTab[i].find(L'}'), 1, L" ");
	}
}
