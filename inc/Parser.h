#ifndef PARSER_H
#define PARSER_H
#include "Functions.h"
#include "FileHandling.h"

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>

typedef std::pair<std::wstring, std::wstring> Pair;
typedef std::multimap<std::wstring, std::wstring> MapCode;

class Parser
{
private:
	std::vector<std::wstring>* mainString;
	std::vector<std::wstring> splitedLine;
	std::vector<std::wstring> special_operators{ L"+=", L"-=", L"*=", L"/=", L"<=",L">=",L"++", L"--", L"!=", L"//", L"<<", L">>", L"**", L"->", L"||" };
	std::vector<std::wstring> operators{ L"=",L"+", L"-", L"/", L"*", L"%", L"&", L"<", L">", L"^", L"!", L"?", L",", L"." }; 

	std::wstring startBlock = L"#define obf_block_start";
	std::wstring endBlock = L"#define obf_block_end";

	std::vector<Variable> variables;
	bool IsContinue(std::vector<indexPair> indexPosition, bool isContinue);


	std::vector<indexPair> FindCharIndex(std::wstring& line, std::wstring _char, bool isContinue);
	std::vector<indexPair> FindBlockIndex();

	void NewNameVariables(std::vector<Variable>& variables, std::wstring word, std::wstring typeOfVariable, int pointerCounter, int arrayDimCounter);

	void AddExpectionsWords();

	int FindForLoop(int startIndex);
	int LengthOfLoop(int startIndex);
	int LengthOfSecondLoop(int startIndex, std::vector<std::wstring> wstringTab);
	void GetVariablesFromFor(std::wstring lineFor, std::wstring* tab, short index, wchar_t _char);
	int GetNameForChangeLoop(std::wstring lineLoop, std::wstring lineLoopSecond, std::wstring& nameOfVar);
	void RemoveBracketOfSecondLoop(int startIndex, int loopLength, std::vector<std::wstring>& wstringTab);

	int ChangeLoop(int indexLoop);


public:
	Parser(std::vector<std::wstring>* ptrContentFile);
	Parser(FileHandling& file, std::string name);
	void SpaceOperators();
	void DeleteComments();

	void SpaceOperatorsFix();

	void FindVariables();
	void ChangeVariables();
	void OperatorException(std::wstring& line, std::wstring findOperator, std::wstring changeOperator, short replace, short find, std::vector<indexPair>& indexPositions);


	void DeleteDoubleSpaces(std::wstring& line);
	void DeleteEnters(); 
	void DeleteUnnecessarySpaces();

	
	void ChangeLoops();


	void AddJunks(int amountOfVariables, int amountOfJunk);

	void AddEncryption(bool toFile = false, bool onlyFors = false);

};

#endif // PARSER_H