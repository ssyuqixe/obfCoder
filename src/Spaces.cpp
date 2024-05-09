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
	std::vector<std::vector<std::wstring>> operatorExceptions = { {L" ; ", L";"}, {L" , ", L","}, {L" ( ", L"("}, {L" [ ", L"["}, {L" { ", L"{"}, {L" ) ", L")"}, {L" ] ", L"]"}, {L" } ", L"}"}, {L"( ", L"("}, {L"[ ", L"["}, {L"{ ", L"{"}, {L" )", L")"}, {L" ]", L"]"}, {L" }", L"}"}};

	for (auto &line : *p_ContentFile)
	{
		if(line.empty())
			continue;
			
		indexPositions.erase(indexPositions.begin(), indexPositions.end());
		indexPositions = FindCharIndex(line, L"\"", isContinue);
		isContinue = p_Parser->IsContinue(indexPositions, isContinue);

		for(const auto& op : operatorExceptions)
			p_Parser->OperatorException(line, op[0], op[1], 2, 1-short(op[0].length()), indexPositions);
		

		for (auto &o : settings::special_operators){
			p_Parser->OperatorException(line, L" " + o + L" ", o, 4, -2, indexPositions);
			p_Parser->OperatorException(line, L" " + o, o, 3, -1, indexPositions);
			p_Parser->OperatorException(line, o + L" ", o, 3, -1, indexPositions);
		}

		for (auto &o : settings::operators){
			p_Parser->OperatorException(line, L" " + o + L" ", o, 3, -2, indexPositions);
			p_Parser->OperatorException(line, L" " + o, o, 2, -1, indexPositions);
			p_Parser->OperatorException(line, o + L" ", o, 2, -1, indexPositions);

		}

		p_Parser->OperatorException(line, L"\t", L"", 1, -1, indexPositions);
		p_Parser->OperatorException(line, L", ", L",", 2, -1, indexPositions);
		p_Parser->OperatorException(line, L" ,", L",", 2, -1, indexPositions);
		p_Parser->OperatorException(line, L"; ", L";", 2, -1, indexPositions);
		p_Parser->OperatorException(line, L" ;", L";", 2, -1, indexPositions);
		p_Parser->DeleteDoubleSpaces(line);
		if(line[0] == L' ')
			line.erase(0, 1);
	}


    return true;
}
