#pragma once
#include <string>
#include <vector>
typedef std::pair<size_t, size_t> indexPair;

const int specialVariables = 2;

struct Variable {
	int isPointer;
	int isArray;
	std::wstring name;
	std::wstring newName;
	std::wstring type;

	Variable(std::wstring Name, std::wstring NewName, std::wstring Type, int IsPointer = 0, int IsArray = 0)
		: name(Name), newName(NewName), type(Type), isPointer(IsPointer), isArray(IsArray) {}

};

inline int CountOfRangeChars(int startIndex, std::vector<std::wstring>& wstringTab)
{
	int countOfRange = 0;
	int indexHelp = 0;

	while (true) {
		if (!wstringTab[startIndex].empty() && wstringTab[startIndex].find(L"{", indexHelp) != std::string::npos) {
			indexHelp = wstringTab[startIndex].find(L"{", indexHelp) + 1;
			countOfRange++;
		}
		else
			break;
	}

	indexHelp = 0;
	while (true) {
		if (!wstringTab[startIndex].empty() && wstringTab[startIndex].find(L"}", indexHelp) != std::string::npos) {
			indexHelp = wstringTab[startIndex].find(L"}", indexHelp) + 1;
			countOfRange--;
		}
		else
			break;
	}

	return countOfRange;
}

template<class T>
inline void Split(const std::wstring& str, T& cont, wchar_t wchar)
{
	std::wistringstream iss(str);
	std::wstring item;
	while (std::getline(iss, item, wchar))
	{
		cont.push_back(item);
	}

}


inline bool CheckInclude(std::wstring line)
{
	if (!line.empty() && line.find(L"#include") != std::wstring::npos)
		return true;
	return false;
}

inline std::vector<indexPair> FindCharIndex(std::wstring& line, std::wstring _char, bool isContinue)
{
	std::vector<size_t> allIndexs;


	size_t startIndex;

	if (!line.empty() && line.find(_char) != std::wstring::npos) {
		startIndex = line.find(_char);
		if (startIndex - 1 >= 0 && line[startIndex - 1] != L'\\') //
			allIndexs.push_back(startIndex);

		while (line.find(_char, startIndex + 1) != std::wstring::npos && startIndex - 1 >= 0 && line[startIndex - 1] != L'\\') {
			startIndex = line.find(_char, startIndex + 1);
			allIndexs.push_back(startIndex);
		}
	}


	std::vector<indexPair> indexVector;

	if (!allIndexs.empty())
		if (isContinue) {
			indexVector.push_back(indexPair(0, allIndexs[0]));
			for (size_t i = 1; i < allIndexs.size() - 1; i += 2)
				indexVector.push_back(indexPair(allIndexs[i], allIndexs[i + 1]));


			if (!(allIndexs.size() % 2))
				indexVector.push_back(indexPair(allIndexs.back(), INT32_MAX));
		}
		else {
			for (size_t i = 0; i < allIndexs.size() - 1; i += 2)
				indexVector.push_back(indexPair(allIndexs[i], allIndexs[i + 1]));

			if (allIndexs.size() % 2)
				indexVector.push_back(indexPair(allIndexs.back(), INT32_MAX));
		}

	return indexVector;

}


inline std::wstring RandomUnicode(size_t len, size_t start, size_t end)
{
	std::wstring ustr;
	size_t intervalLength = end - start + 1;

	for (auto i = 0; i < len; i++) {
		ustr += (rand() % intervalLength) + start;
	}

	return ustr;
}


inline std::wstring RandomUnicodeUntilNewValue(size_t len, size_t start, size_t end, std::vector<std::wstring> container) {
	std::wstring newString = RandomUnicode(len, start, end);
	//int counter == 0;
	if (container.empty() == false) {
		for (int i = 0; i < container.size(); i++)
			if (container[i].compare(newString) == 0) {
				newString = RandomUnicode(len, start, end);
				i = 0;
				//counter++;
				//if (counter > (end - start) * 3) {
				//	
				//}
				break;
			}
	}
	return newString;
}
