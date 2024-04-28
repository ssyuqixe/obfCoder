#include "Enters.h"
#include "Functions.h"


bool Enters::Update(std::vector<int> &settings)
{
    return true;
}

bool Enters::DoTechnique()
{
	bool isContinue = false;
	std::vector<indexPair> indexPositions;

	for (auto &line : *p_ContentFile)
	{

		indexPositions.erase(indexPositions.begin(), indexPositions.end());
		indexPositions = FindCharIndex(line, L"\"", isContinue);
		isContinue = p_Parser->IsContinue(indexPositions, isContinue);

		if (!line.empty() && !CheckInclude(line) && line.find(L"#define") == std::string::npos)
		{
			p_Parser->OperatorException(line, L"\n", L"", 1, -1, indexPositions);
		}

		// else if (!line.empty())
		//	line = L"\n" + line;
	}

    return true;
}