#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <random>

typedef std::pair<size_t, size_t> indexPair;

//check later why it is hardcoded
const int specialVariables = 2;	

struct RandomEngine{
	std::random_device rd;
	std::mt19937 gen;
	RandomEngine() : gen(rd()) {}
};
static RandomEngine randomEngine;


struct Variable {
	int isPointer;
	int isArray;
	std::wstring name;
	std::wstring newName;
	std::wstring type;

	Variable(std::wstring Name, std::wstring NewName, std::wstring Type, int IsPointer = 0, int IsArray = 0)
		: name(Name), newName(NewName), type(Type), isPointer(IsPointer), isArray(IsArray) {}

};

inline int CountOfRangeChars(const std::wstring& wstringLine)
{
	if(wstringLine.empty())
		return 0;
	
	int countOfRange = 0;
	for(const auto& c : wstringLine)
		if (c == L'{')
			countOfRange++;
		else if (c == L'}')
			countOfRange--;

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
	return (!line.empty() && line.find(L"#include") != std::wstring::npos) ? true : false;
}

//check
inline std::vector<indexPair> FindCharIndex(std::wstring& line, std::wstring _char, bool isContinue)
{
	std::vector<size_t> allIndexs;
	size_t startIndex = 0;
	std::vector<indexPair> indexVector;

	if(line.empty())
		return indexVector;

	while(line.find(_char, startIndex) != std::wstring::npos)
	{
		if(int(startIndex) - 1 >= 0 && line[startIndex - 1] != L'\\'){
			startIndex = line.find(_char, startIndex);
			allIndexs.push_back(startIndex);
		}
		startIndex++;
	}


	//need to understand the logic behind it
	if(!allIndexs.empty()){
		if(isContinue)
			indexVector.push_back(indexPair(0, allIndexs[0]));

		for(size_t i = (int)(isContinue); i < allIndexs.size() - 1; i += 2)
			indexVector.push_back(indexPair(allIndexs[i], allIndexs[i + 1]));
		if(isContinue && !(allIndexs.size() % 2))
			indexVector.push_back(indexPair(allIndexs.back(), INT32_MAX));
		else if(allIndexs.size() % 2)
			indexVector.push_back(indexPair(allIndexs.back(), INT32_MAX));
	}

	return indexVector;

}


inline std::wstring RandomUnicode(size_t len, size_t start, size_t end)
{
	std::wstring ustr;
	ustr.resize(len);
	size_t intervalLength = end - start + 1;

	for (int i = 0; i < len; i++)
		ustr[i] = (wchar_t)((randomEngine.gen() % intervalLength) + start);
	return ustr;
}


inline std::wstring RandomUnicodeUntilNewValue(size_t len, size_t start, size_t end, std::vector<std::wstring> container) {

	bool isUnique = false;
	std::wstring newString = RandomUnicode(len, start, end);
	if (container.empty())
		return newString;
	//I assume that len is long enough to cover all generations
	//Maybe in future add mechanism to check if all possible values are used
	do {
		isUnique = true;
		for (int i = 0; i < container.size(); i++)
			if (container[i].compare(newString) == 0){
				isUnique = false;
				newString =  RandomUnicode(len, start, end);
				break;
			}
	} while(isUnique == false);
	return newString;
}


#endif // FUNCTIONS_H