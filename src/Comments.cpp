#include "Comments.h"
#include <iostream>

bool Comments::Update(std::vector<int> &settings)
{
	return true;
}

bool Comments::DoTechnique()
{	
	//DeleteBlockComments();
	//DeleteLineComments();
	return DeleteBlockComments();
}

bool Comments::DeleteLineComments()
{
    throw std::runtime_error("Not implemented");
}

bool Comments::DeleteBlockComments()
{
    //temporary both cases in one function
    bool commentLong = false;
	for (auto &line : *p_ContentFile)
	{
		if (!commentLong && !line.empty() && line.find(L"/*") != std::string::npos)
		{

			if (line.find(L"\"/*\"") == std::string::npos && line.find(L"\"*/\"") == std::string::npos && line.find(L"\\\"") == std::string::npos)
			{
				if (line.rfind(L"*/") != std::string::npos && line.rfind('*/') != line.find(L"/*") + 1)
				{ // case for /*   */ in one line
					line.erase(line.find(L"/*"), line.rfind(L"*/") + 1);
				}
				else if (line.find(L"*/") != std::string::npos && line.find('*/') == line.find(L"/*") + 1 && line.find(L"*/") == line.rfind(L"*/"))
				{
					line.erase(line.find(L"/*", line.length() - 1)); // case for /*/*/, checking if there is /*/ and last is */ or /*/
					commentLong = true;
				}
				else
				{
					line.erase(line.find(L"/*"), line.length() - 1); // deleting all comments if there is not */ in the line
					commentLong = true;
				}
			}
		}

		if (commentLong && !line.empty() && line.rfind(L"*/") != std::string::npos)
		{ // checking if there is */ and stop deleting
			line.erase(0, line.find(L"*/") + 2);
			commentLong = false;
		}

		if (commentLong) // just delete comments if there isn't /* or */
			line.erase();

		if (!commentLong && !line.empty() && line.find(L"//") != std::string::npos && line.find(L"\"//\"") == std::string::npos)
			line.erase(line.find(L"//"), line.length() - line.find(L"//") - 1);
	}
    return true;
}