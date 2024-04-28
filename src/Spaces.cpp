#include "Spaces.h"
#include "Functions.h"
#include "Settings.h"
#include <iostream>
#include <vector>
#include <string>

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
		isContinue = p_Parser->IsContinue(indexPositions, isContinue);

		// p_Parser->OperatorException(line, L" ' ", L"'", 2, -2, indexPositions);
		p_Parser->OperatorException(line, L" ; ", L";", 2, -2, indexPositions);
		p_Parser->OperatorException(line, L" , ", L",", 3, -2, indexPositions);
		p_Parser->OperatorException(line, L" ( ", L"(", 2, -2, indexPositions);
		p_Parser->OperatorException(line, L" [ ", L"[", 2, -2, indexPositions);
		p_Parser->OperatorException(line, L" { ", L"{", 2, -2, indexPositions);
		p_Parser->OperatorException(line, L" ) ", L")", 2, -2, indexPositions);
		p_Parser->OperatorException(line, L" ] ", L"]", 2, -2, indexPositions);
		p_Parser->OperatorException(line, L" } ", L"}", 2, -2, indexPositions);

		p_Parser->OperatorException(line, L"( ", L"(", 2, -1, indexPositions);
		p_Parser->OperatorException(line, L"[ ", L"[", 2, -1, indexPositions);
		p_Parser->OperatorException(line, L"{ ", L"{", 2, -1, indexPositions);
		p_Parser->OperatorException(line, L" )", L")", 2, -1, indexPositions);
		p_Parser->OperatorException(line, L" ]", L"]", 2, -1, indexPositions);
		p_Parser->OperatorException(line, L" }", L"}", 2, -1, indexPositions);
		// p_Parser->OperatorException(line, L"' ", L"'", 2, -1, indexPositions);
		// p_Parser->OperatorException(line, L" '", L"'", 2, -1, indexPositions);

		for (auto &o : settings::special_operators)
			p_Parser->OperatorException(line, L" " + o + L" ", o, 4, -2, indexPositions);

		for (auto &o : settings::operators)
			p_Parser->OperatorException(line, L" " + o + L" ", o, 3, -2, indexPositions);

		p_Parser->OperatorException(line, L"\t", L"", 1, -1, indexPositions);
		// p_Parser->OperatorException(line, L", ", L",", 2, -1, indexPositions);
		p_Parser->OperatorException(line, L" ,", L",", 2, -1, indexPositions);
		p_Parser->OperatorException(line, L"; ", L";", 2, -1, indexPositions);
		p_Parser->OperatorException(line, L" ;", L";", 2, -1, indexPositions);
	}
    return true;
}
