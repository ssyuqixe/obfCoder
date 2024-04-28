#include "Renamer.h"
#include "Functions.h"
#include <iostream>
#include <vector>
#include <string>

bool Renamer::Update(std::vector<int> &settings)
{
	if(p_Parser == nullptr)
		return false;
	p_Parser->FindVariables();
    return true;
}

bool Renamer::DoTechnique()
{	
    size_t index;
	int diff;
	bool isNotInRange;
	bool isContinue = false;
	size_t indexOfPair;
	std::vector<indexPair> indexPositions;

	for (auto &line : *p_ContentFile)
	{
		if (line.empty() == true)
			continue;

		index = 0;
		diff = 0;

		indexPositions.erase(indexPositions.begin(), indexPositions.end());
		indexPositions = FindCharIndex(line, L"\"", isContinue);

		isContinue = IsContinue(indexPositions, isContinue);

		while (line.find(L" false ") != std::string::npos)
		{
			index = line.find(L" false ", 0);
			line.replace(index, 7, L" 0 ");
		}
		while (line.find(L" true ") != std::string::npos)
		{
			index = line.find(L" true ", 0);
			line.replace(index, 6, L" 1 ");
		}

		for (auto const &variable : *p_Variables)
		{
			if (line.find(L" " + variable.name + L" ") != std::string::npos)
			{
				index = line.find(L" " + variable.name + L" ");
				indexOfPair = 0;
				while (line.find(L" " + variable.name + L" ", index) != std::string::npos)
				{
					isNotInRange = true;
					if (!indexPositions.empty())
						for (size_t i = 0; i < indexPositions.size(); i++)
						{
							if (indexPositions[i].first < index && index < indexPositions[i].second)
							{
								isNotInRange = false;
								indexOfPair = i;
								break;
							}
						}

					if (isNotInRange)
					{
						diff = (int)(variable.newName.length() - variable.name.length()); // counting the length of diffrence new name - old name
						line.replace(index, variable.name.length() + 2, L" " + variable.newName + L" ");
						index = line.find(L" " + variable.name + L" ", index + variable.name.length() + diff);

						if (!indexPositions.empty())
						{
							// indexPositions[indexOfPair].second += diff;

							for (size_t i = indexOfPair + 1; i < indexPositions.size(); i++)
							{
								indexPositions[i].first += diff;
								indexPositions[i].second += diff;
							}
						}
					}
					else
						index = line.find(L" " + variable.name + L" ", index + variable.name.length());
				}
			}
		}
	}
    return true;
}


bool Renamer::IsContinue(std::vector<indexPair> indexPosition, bool isContinue)
{
	if (!indexPosition.empty())
		isContinue = (indexPosition.back().second >= INT32_MAX) ? true : false;
	return isContinue;
}