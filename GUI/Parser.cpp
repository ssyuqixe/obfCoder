
#include "Parser.h"
#include <map>
#include <ctime>
#include <codecvt>
#include "Encryption.h"
#include "Junker.h"

bool Parser::IsContinue(std::vector<indexPair> indexPosition, bool isContinue)
{
	if (!indexPosition.empty())
		if (indexPosition.back().second >= INT32_MAX) return true;
		else if (indexPosition.back().second < INT32_MAX)
			return false;
	 return isContinue;
}

Parser::Parser(std::string name)
{
	iFile.open(name);
	this->mainString = LoadFile(this->iFile);

	AddExpectionsWords();
}

std::vector<std::wstring> Parser::LoadFile(std::wifstream& iFile)
{

	std::vector<std::wstring> stringVector;
	if (!iFile) {
		std::cout << "Cannot open the file!" << std::endl;
		isError = true;
		return stringVector;
	}


	std::wstring str;
	while (std::getline(iFile, str))
	{
		str += L"\n";
		stringVector.push_back(str);
	}

	// Deleting character set, which sometimes generate at start of file
	if (!stringVector[0].empty() && stringVector[0].find(L"ï»¿") != std::wstring::npos) 
		stringVector[0].erase(stringVector[0].find(L"ï»¿"), 3);							

	iFile.close();
	return stringVector;
}

void Parser::SaveFile(std::string name)
{

	std::locale loc(std::locale(), new std::codecvt_utf8_utf16<wchar_t>);
	std::basic_ofstream<wchar_t> ofs(name);
	ofs.imbue(loc);

	this->oFile.open(name);
	for (auto& line : this->mainString)
	{
		ofs << line << std::flush;
	}

	this->oFile.close();
}

void Parser::SpaceOperators()
{
	std::vector<std::wstring> sufix{ L"=", L"+", L"-", L"*", L"/", L"<", L">", L"&", L"|", L"^", L"!" };
	std::vector<int> positions; 
	std::vector<indexPair> indexPositions;
	std::vector<indexPair> indexPositionsBlock;
	size_t index = 0;
	size_t indexOfPair = 0;

	bool isChange = true;
	bool isContinue = false;
	bool isNotInRange;

	for (auto& line : this->mainString) {
		if (CheckInclude(line))
			continue;


		indexPositions.erase(indexPositions.begin(), indexPositions.end());
		indexPositions = FindCharIndex(line, L"\"", isContinue);

		isContinue = IsContinue(indexPositions, isContinue);


		for (auto& o : special_operators)
			OperatorException(line, o, L" " + o + L" ", 2, 2, indexPositions);

		// Exception for (, [, ), ]
		OperatorException(line, L";", L" ; ", 1, 2, indexPositions);
		OperatorException(line, L"\t", L" \t ", 1, 2, indexPositions);
		OperatorException(line, L"(", L"( ", 1, 1, indexPositions);
		OperatorException(line, L"[", L" [ ", 1, 2, indexPositions);
		OperatorException(line, L")", L" )", 1, 1, indexPositions);
		OperatorException(line, L"]", L" ] ", 1, 2, indexPositions);
		// !!


		for (auto& op : operators) {
			isChange = true;

			if (!line.empty() && line.find(op) != std::string::npos) {
				index = line.find(op);


				while (line.find(op, index) != std::string::npos) {
					isChange = true;
					isNotInRange = true;
					indexOfPair = 0;

					for (size_t i = 0; i < indexPositions.size(); i++) {
						if (indexPositions[i].first < index && index < indexPositions[i].second) {
							isNotInRange = false;
							indexOfPair = i;
							break;
						}
					}


					if (isNotInRange == true) {
						for (auto& c : sufix)		//Check if there is a double operator
							if ((index - 1 >= 0 && index + 1 < line.length()) && (line[index + 1] == c[0] || line[index - 1] == c[0]))
								isChange = false;
						if (op.compare(L".") == 0) { //Check if number is float
							if (index - 1 >= 0) {
								std::vector<std::wstring> container;
								Split(line.substr(0, line.find(op, index) + 1), container, L' ');
								if (container.empty() == false  && isdigit(container.back()[0])) {
									isChange = false;
								}
							}
						}

						if (isChange) {
							line.replace(index, 1, L" " + op + L" ");
							index = line.find(op, index + 2);

							if (!indexPositions.empty()) {

								for (size_t i = indexOfPair + 1; i < indexPositions.size(); i++) {
									indexPositions[i].first += 2;
									indexPositions[i].second += 2;
								}
							}
						}
						else
							index = line.find(op, index + 1);

					}
					else
						if (index + 1 < line.length())
							index = line.find(op, index + 1);
						else
							break;


				}
			}
		}

		DeleteDoubleSpaces(line);
	}
}

//Add space after search variable names e.g. for a constructor
void Parser::SpaceOperatorsFix()
{
	std::vector<indexPair> indexPositions;
	bool isContinue = false;

	for (auto& line : this->mainString) {

		if (CheckInclude(line))
			continue;

		indexPositions.erase(indexPositions.begin(), indexPositions.end());

		indexPositions = FindCharIndex(line, L"\"", isContinue);


		isContinue = IsContinue(indexPositions, isContinue);


		OperatorException(line, L";", L" ; ", 1, 2, indexPositions);
		//OperatorException(line, L"'", L" ' ", 1, 2, indexPositions);
		OperatorException(line, L",", L" , ", 1, 2, indexPositions);
		OperatorException(line, L"(", L" ( ", 1, 2, indexPositions);
		OperatorException(line, L"[", L" [ ", 1, 2, indexPositions);
		OperatorException(line, L"{", L" { ", 1, 2, indexPositions);
		OperatorException(line, L")", L" ) ", 1, 2, indexPositions);
		OperatorException(line, L"]", L" ] ", 1, 2, indexPositions);
		OperatorException(line, L"}", L" } ", 1, 2, indexPositions); 

		DeleteDoubleSpaces(line);

	}
}

void Parser::DeleteComments()
{
	bool commentLong = false;
	for (auto& line : mainString) {
		if (!commentLong && !line.empty() && line.find(L"/*") != std::string::npos) {

			if (line.find(L"\"/*\"") == std::string::npos && line.find(L"\"*/\"") == std::string::npos && line.find(L"\\\"") == std::string::npos) {
				if (line.rfind(L"*/") != std::string::npos && line.rfind('*/') != line.find(L"/*") + 1) { // case for /*   */ in one line
					line.erase(line.find(L"/*"), line.rfind(L"*/") + 1);
				}
				else if (line.find(L"*/") != std::string::npos && line.find('*/') == line.find(L"/*") + 1 && line.find(L"*/") == line.rfind(L"*/")) {
					line.erase(line.find(L"/*", line.length() - 1)); //case for /*/*/, checking if there is /*/ and last is */ or /*/
					commentLong = true;
				}
				else {
					line.erase(line.find(L"/*"), line.length() - 1); //deleting all comments if there is not */ in the line
					commentLong = true;
				}
			}
		}

		if (commentLong && !line.empty() && line.rfind(L"*/") != std::string::npos) { //checking if there is */ and stop deleting
			line.erase(0, line.find(L"*/") + 2);
			commentLong = false;
		}

		if (commentLong) //just delete comments if there isn't /* or */
			line.erase();

		if (!commentLong && !line.empty() && line.find(L"//") != std::string::npos && line.find(L"\"//\"") == std::string::npos)
			line.erase(line.find(L"//"), line.length() - line.find(L"//") - 1);
	}
}

void Parser::FindVariables()
{

	std::vector<std::wstring> typesOfVariables{ L"int", L"double", L"float", L"string", L"uint8_t", L"uint16_t", L"uint32_t", L"uint64_t", L"int8_t", L"int16_t", L"int32_t", L"int64_t", L"char", L"char16_t", L"char32_t", L"bool", L"short", L"wchar_t", L"size_t"  }; //L"void"

	bool save = false;
	bool next = false;
	bool change = false;
	std::wstring typeOfVariable;
	size_t iter = 0;
	int pointerCounter = 0;
	int arrayDimCounter = 0;

	for (auto& line : this->mainString) {
		iter++;
		Split(line, this->splitedLine, L' ');


		if (!line.empty() && line.find(L"#include") != std::string::npos) 
			continue;

		for (int i = 0; i < splitedLine.size(); i++) {

			next = false;
			if (!splitedLine[i].empty() && splitedLine[i].find(L'(') != std::string::npos) { //Stop searching in line if there is a function by using "(" with name
				save = false;
				continue;
			}
			if (save && !splitedLine[i].empty() && splitedLine[i].find(L'&') != std::string::npos) { //Stop searching in line if there is a function by using "(" with name
				next = true;
				continue;
			}
			if (save && !splitedLine[i].empty() && splitedLine[i].find(L'*') != std::string::npos) {
				next = true;

				if (splitedLine[i].find(L"**") != std::string::npos)
					pointerCounter += 2;
				else
					pointerCounter++;
				continue;
			}


			for (auto& type : typesOfVariables)
				if (!next && !line.empty() && line.find(type) != std::string::npos)
					if (splitedLine[i].compare(type) == 0) { //Checking if text is type of variable
						save = true;	//set to save next word
						next = true;	//set to check next word
						typeOfVariable = type;
						break;
					}
			if (save && !next) {  
				save = false;



				change = true;
				if (splitedLine[i] == L">" || splitedLine[i] == L">>" || splitedLine[i] == L";" || splitedLine[i] == L"," || splitedLine[i] == L"const") change = false;
				

				
				///*
				if (i - 2 >= 0 && splitedLine[i - 2] == L"const") {
					change = false;
				}//*/

				if(change == true)
					for (auto& variable : variables) {
						if (variable.newName == splitedLine[i]) {
							change = false;
							pointerCounter = 0;
							break;
						}
					}



				if (change == true){
					arrayDimCounter = 0;
					/*
					if ((i + 2 < splitedLine.size()) && splitedLine[i + 2].compare(L"new") == 0) {

					}*/
					bool startedArray = false;
					if (i + 1 < splitedLine.size() && splitedLine[i + 1].compare(L"[") == 0) {
						startedArray = true;
						for (int u = i + 2; u < splitedLine.size(); u++) {
							if (startedArray && splitedLine[u].compare(L"]") == 0) {
								arrayDimCounter++;
								startedArray = false;
								if (u + 1 < splitedLine.size() && splitedLine[u + 1].compare(L"[") == 0) {
									startedArray = true;
									u++;
								}
							}



						}
					}


					NewNameVariables(variables, splitedLine[i], typeOfVariable, pointerCounter, arrayDimCounter);
				}
			}
		}
		this->splitedLine.erase(this->splitedLine.begin(), this->splitedLine.end());
	}
}

std::vector<indexPair> Parser::FindCharIndex(std::wstring& line, std::wstring _char, bool isContinue)
{
	std::vector<size_t> allIndexs;


	size_t startIndex;

	if (!line.empty() && line.find(_char) != std::wstring::npos) {
		startIndex = line.find(_char);
		if(startIndex - 1 >= 0 && line[startIndex - 1] != L'\\') //
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

std::vector<indexPair> Parser::FindBlockIndex()
{
	std::vector<indexPair> indexVector;
	bool isBlockStarted = false;
	size_t startIndex;

	int i = 0; 
	for (auto& line : this->mainString) {
		if (!line.empty() && line.find(startBlock) != std::wstring::npos) {
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

void Parser::NewNameVariables(std::vector<Variable>& variables, std::wstring word, std::wstring typeOfVariable, int pointerCounter, int arrayDimCounter)
{
	//std::wstring newName = randomUnicode(10, 0x0041, 0x005A); //A-Z
	std::wstring newName = RandomUnicode(1, 0x4E00, 0x62FF);  // chinese 0x62FF
	int i = 1;
	bool change;
	while (true) {
		change = false;

		for (auto& element : variables) {
			if (element.newName == newName) {
				newName = RandomUnicode(++i, 0x4E00, 0x62FF);
				change = true;
				break;
			}
		}

		if (!change) break;

	}
	variables.push_back(Variable(word, newName, typeOfVariable, pointerCounter, arrayDimCounter));
	//mapVariables.insert(Pair(word, newName));
}

void Parser::ChangeVariables()
{
	size_t index;
	int diff;
	bool isNotInRange;
	bool isContinue = false;
	size_t indexOfPair;
	std::vector<indexPair> indexPositions;

	for (auto& line : this->mainString) {
		if (line.empty() == true)
			continue;

		index = 0;
		diff = 0;

		indexPositions.erase(indexPositions.begin(), indexPositions.end());
		indexPositions = FindCharIndex(line, L"\"", isContinue);

		isContinue = IsContinue(indexPositions, isContinue);
		

		while(line.find(L" false ") != std::string::npos)
		{
			index = line.find(L" false ", 0);
			line.replace(index, 7, L" 0 ");
		}
		while (line.find(L" true ") != std::string::npos)
		{
			index = line.find(L" true ", 0);
			line.replace(index, 6, L" 1 ");
		}


		for (auto const& variable : this->variables) {
			if (line.find(L" " + variable.name + L" ") != std::string::npos) { 
				index = line.find(L" " + variable.name + L" "); 
				indexOfPair = 0;
				while (line.find(L" " + variable.name + L" ", index) != std::string::npos) { 
					isNotInRange = true;
					if (!indexPositions.empty())
						for (size_t i = 0; i < indexPositions.size(); i++) {
							if (indexPositions[i].first < index && index < indexPositions[i].second) {
								isNotInRange = false;
								indexOfPair = i;
								break;
							}
						}


					if (isNotInRange) {
						diff = variable.newName.length() - variable.name.length(); //counting the length of diffrence new name - old name
						line.replace(index, variable.name.length() + 2, L" " + variable.newName + L" "); 
						index = line.find(L" " + variable.name + L" ", index + variable.name.length() + diff); 



						if (!indexPositions.empty()) {
							//indexPositions[indexOfPair].second += diff;

							for (size_t i = indexOfPair + 1; i < indexPositions.size(); i++) {
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

}

void Parser::OperatorException(std::wstring& line, std::wstring findOperator, std::wstring changeOperator, short replace, short find, std::vector<indexPair>& indexPositions)
{
	size_t index;
	int indexOfPair = 0;
	bool isNotInRange;
	bool isHaveToChangeIndex;
	if (!line.empty() && line.find(findOperator) != std::wstring::npos) {
		index = line.find(findOperator);
		while (line.find(findOperator, index) != std::wstring::npos) {
			isNotInRange = true;
			isHaveToChangeIndex = false;
			if (!indexPositions.empty())
				for (size_t i = 0; i < indexPositions.size(); i++) {
					if (indexPositions[i].first <= index && index <= indexPositions[i].second) {
						isNotInRange = false;
						indexOfPair = i;
						break;
					}

					if (index < indexPositions[i].first) {
						isHaveToChangeIndex = true;
					}

				}

			if (isNotInRange) {
				line.replace(index, replace, changeOperator);

				if (!indexPositions.empty() && isHaveToChangeIndex == true) {
					if (index < indexPositions[0].first)
						indexOfPair = -1;
					for (size_t i = indexOfPair + 1; i < indexPositions.size(); i++) {
						indexPositions[i].first += find;
						indexPositions[i].second += find;
					}
					if(indexOfPair == -1)
						indexOfPair = 0;
				}

				index = line.find(findOperator, index + find + 1);

			}
			else
				index = line.find(findOperator, index + 1);
		}
	}

}

void Parser::DeleteDoubleSpaces(std::wstring& line)
{
	while (true) {
		if (!line.empty() && line.find(L"  ") != std::wstring::npos) {
			line.replace(line.find(L"  "), 2, L" ");
		}
		else
			break;
	}

}

void Parser::DeleteEnters()
{
	bool isContinue = false;
	size_t indexOfPair;
	size_t index;
	std::vector<indexPair> indexPositions;

	for (auto& line : mainString) {

		indexPositions.erase(indexPositions.begin(), indexPositions.end());
		indexPositions = FindCharIndex(line, L"\"", isContinue);
		isContinue = IsContinue(indexPositions, isContinue);


		if (!line.empty() && !CheckInclude(line) && line.find(L"#define") == std::string::npos ) {
			OperatorException(line, L"\n", L"", 1, -1, indexPositions);
		}
		
		//else if (!line.empty())
		//	line = L"\n" + line;
	}
}

void Parser::DeleteUnnecessarySpaces()
{

	bool isContinue = false;
	std::vector<indexPair> indexPositions;

	for (auto& line : mainString) {

		indexPositions.erase(indexPositions.begin(), indexPositions.end());
		indexPositions = FindCharIndex(line, L"\"", isContinue);
		isContinue = IsContinue(indexPositions, isContinue);

		//OperatorException(line, L" ' ", L"'", 2, -2, indexPositions);
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
		//OperatorException(line, L"' ", L"'", 2, -1, indexPositions);
		//OperatorException(line, L" '", L"'", 2, -1, indexPositions);


		for (auto& o : special_operators)
			OperatorException(line, L" " + o + L" ", o , 4, -2, indexPositions);
		
		for (auto& o : operators)
			OperatorException(line, L" " + o + L" ", o, 3, -2, indexPositions);

		OperatorException(line, L"\t", L"", 1, -1, indexPositions);
		//OperatorException(line, L", ", L",", 2, -1, indexPositions);
		OperatorException(line, L" ,", L",", 2, -1, indexPositions);
	    OperatorException(line, L"; ", L";", 2, -1, indexPositions);
		OperatorException(line, L" ;", L";", 2, -1, indexPositions);
	}
}

std::vector<std::wstring> Parser::GetMainString()
{
	return this->mainString;
}

void Parser::AddExpectionsWords()
{
	//mapVariables.insert(Pair(L" operator ", L"operator"));
	//mapVariables.insert(Pair(L" NULL ", L"NULL"));
	//mapVariables.insert(Pair(L" [ ", L"["));

	variables.push_back(Variable(L" operator ", L"operator", L"special"));
	variables.push_back(Variable(L" NULL ", L"NULL", L"special"));
	variables.push_back(Variable(L" [ ", L"[", L"special"));
	//variables.push_back(Variable(L"false", L"0", L"special"));
	//variables.push_back(Variable(L"true", L"1", L"special"));
	//variables.insert(variables.begin(), Variable(word, newName, typeOfVariable));
}

int Parser::FindForLoop(int startIndex)
{
	int index = -1;

	std::vector<indexPair> indexBlockPosition = FindBlockIndex();


	int countOfRange = 0;
	bool isSecondLoopInRange = false;

	for (int i = startIndex; i < mainString.size(); i++) {

		if (!indexBlockPosition.empty())
		{
			for (auto& indexes : indexBlockPosition)
			{
				if (i < indexes.first)
					break;

				if (i >= indexes.first && i <= indexes.second) {
					i = indexes.second + 1;
				}
			}
		}

		if(isSecondLoopInRange &&!mainString[i].empty() && mainString[i].find(L"for") != std::wstring::npos && countOfRange == 1)
		{

			return index;
		}


		if (isSecondLoopInRange && !mainString[i].empty()) {
			int pos = CountOfRangeChars(i, mainString);
			countOfRange += pos;

			if (pos < 0 && countOfRange == 0)
				isSecondLoopInRange = false;

		}


		if (!mainString[i].empty() && mainString[i].find(L" for ") != std::wstring::npos) {

			isSecondLoopInRange = true;
			countOfRange += CountOfRangeChars(i, mainString);
			index = i;
		}

	}
	return -1;
}

int Parser::LengthOfLoop(int startIndex)
{
	bool isStartedRange = false;
	int length = 0;
	int countOfRange = 0;
	int index = startIndex;

	while (true) {
		length++;
		if (isStartedRange == false && countOfRange == 0 && CountOfRangeChars(index, mainString) > 0)
			isStartedRange = true;
		countOfRange += CountOfRangeChars(index, mainString);

		if (isStartedRange == true && countOfRange == 0)
			break;

		index++;
	}



	return length;
}

int Parser::LengthOfSecondLoop(int startIndex, std::vector<std::wstring> wstringTab)
{
	int lengthOfSecondLoop = 0;
	int countOfSecondRange = 0;
	while (true) {
		lengthOfSecondLoop++;
		countOfSecondRange += CountOfRangeChars(startIndex, wstringTab);

		if (countOfSecondRange == 0){
			return lengthOfSecondLoop;
		}
		startIndex++;
	}
	return 0;

}

void Parser::GetVariablesFromFor(std::wstring lineFor, std::wstring* tab, short index, wchar_t _char)
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

int Parser::GetNameForChangeLoop(std::wstring lineLoop, std::wstring lineLoopSecond, std::wstring& nameOfVar)
{

	std::vector<std::wstring> contSplitedBySemicolon;
	std::vector<std::wstring> contSplitedByLowlyChar;


	Split(lineLoop, contSplitedBySemicolon, L';');
	Split(contSplitedBySemicolon[2], contSplitedByLowlyChar, L' ');
	if (contSplitedByLowlyChar.size() == 5) //i += 5
	{
		if (contSplitedByLowlyChar[2].compare(L"+=") != 0 && contSplitedByLowlyChar[2].compare(L"++") != 0)
			return 1;

		if (contSplitedByLowlyChar[2].compare(L"++") == 0)
			contSplitedByLowlyChar[3] = L"1";
		nameOfVar = L" ( " + nameOfVar + L" * " + contSplitedByLowlyChar[3] + L" ) ";

	}
	else if (contSplitedByLowlyChar.size() == 7) { //i = i + 5;		
		if (contSplitedByLowlyChar[4].compare(L"+") != 0)
			return 1;

		if (contSplitedByLowlyChar[5].empty())
			contSplitedByLowlyChar[5] = L"1";
		nameOfVar = L" ( " + nameOfVar + L" * " + contSplitedByLowlyChar[5] + L" ) ";

	}

	contSplitedByLowlyChar.erase(contSplitedByLowlyChar.begin(), contSplitedByLowlyChar.end());

	Split(contSplitedBySemicolon[0], contSplitedByLowlyChar, L'=');

	while (contSplitedByLowlyChar[1].find(L' ') != std::string::npos) {
		contSplitedByLowlyChar[1].erase(contSplitedByLowlyChar[1].find(L' '), 1);
	}
	if (contSplitedByLowlyChar[1].compare(L"0") != 0)
		return 1;

	contSplitedBySemicolon.erase(contSplitedBySemicolon.begin(), contSplitedBySemicolon.end());
	contSplitedByLowlyChar.erase(contSplitedByLowlyChar.begin(), contSplitedByLowlyChar.end());

	Split(lineLoopSecond, contSplitedBySemicolon, L';');
	Split(contSplitedBySemicolon[0], contSplitedByLowlyChar, L'=');

	while (contSplitedByLowlyChar[1].find(L' ') != std::string::npos) {
		contSplitedByLowlyChar[1].erase(contSplitedByLowlyChar[1].find(L' '), 1);
	}
	if (contSplitedByLowlyChar[1].compare(L"0") != 0)
		return 1;
	return 0;
}

void Parser::RemoveBracketOfSecondLoop(int startIndex, int loopLength, std::vector<std::wstring>& wstringTab)
{
	int countOfRange = 0;
	for (int i = startIndex; i < loopLength - 1; i++) { // 1
		int cOR = CountOfRangeChars(i, wstringTab);
		countOfRange += cOR;
		if (cOR > 0 && countOfRange == 1) //>0
			wstringTab[i].replace(wstringTab[i].find(L'{'), 1, L" ");
		else if (cOR < 0 && countOfRange == 0) //>= 0
			wstringTab[i].replace(wstringTab[i].find(L'}'), 1, L" ");
	}

}

int Parser::ChangeLoop(int indexLoop)
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
		copyOfLoop[i].assign(mainString[i + indexOfLoop]);


	GetVariablesFromFor(copyOfLoop[0], nameOfVar1, 1, L' ');
	for (int i = 1; i < loopLength; i++) {
		if (copyOfLoop[i].find(L"for") != std::string::npos) {
			GetVariablesFromFor(copyOfLoop[i], nameOfVar2, 1, L' ');
			indexOfSecondLoop = i;
			break;
		}
	}


	nameOfVar2If = nameOfVar2[1];

	if (GetNameForChangeLoop(copyOfLoop[0], copyOfLoop[indexOfSecondLoop], nameOfVar2If))
		return indexOfLoop + loopLength;
	
	//indexOfLoop + loopLength;

	copyOfLoop.erase(copyOfLoop.begin() + indexOfSecondLoop);
	



	std::wstring forMain = L"for( int t = 0 ; t < ( " + nameOfVar1[1] + L" * " + nameOfVar2[1] + L" ) ; t ++ )\n\0";
	copyOfLoop.front() = forMain;

	int diff;
	for (int i = 1; i < loopLength - 1; i++) {
		index = 0;
		diff = 0;
		while (true) {
			if (!copyOfLoop[i].empty() && copyOfLoop[i].find(L" " + nameOfVar1[0] + L" ", index ) != std::string::npos) {
				index = copyOfLoop[i].find(L" " + nameOfVar1[0] + L" ", index);
				copyOfLoop[i].replace(index + 1, nameOfVar1[0].length(), L" ( t / " + nameOfVar2If + L" ) ");
				diff = nameOfVar2[1].length() - nameOfVar1[0].length();
				index++;
			}
			else
				break;
		}

		index = 0;
		diff = nameOfVar2[1].length() - nameOfVar2[0].length();
		while (true) {
			if (!copyOfLoop[i].empty() && copyOfLoop[i].find(L" " + nameOfVar2[0] + L" ",index) != std::string::npos) {
				index = copyOfLoop[i].find(L" " + nameOfVar2[0] + L" ", index);
				copyOfLoop[i].replace(index + 1, nameOfVar2[0].length(), L" ( t % " + nameOfVar2If + L" ) ");
				index++;
			}
			else
				break;
		}

	}


	int lengthOfSecondLoop = LengthOfSecondLoop(indexOfSecondLoop, copyOfLoop);
	RemoveBracketOfSecondLoop(indexOfSecondLoop, loopLength, copyOfLoop);

	//if




	bool isSomething = false;
	for (int i = 1; i < indexOfSecondLoop; i++) {
		if(!copyOfLoop[i].empty())
			for (auto& _char : copyOfLoop[i]) {
				if (((_char >= 65) && (_char <= 90)) || ((_char >= 97) && (_char <= 122))) {
					isSomething = true;
					break;
				}

			}
		if (isSomething)
			break;
	}

	if(isSomething){
		std::wstring ifwstring = L"\t if( t % ( " + nameOfVar2If + L" ) == 0 )\n\0";
		copyOfLoop.insert(copyOfLoop.begin() + 2, ifwstring);
		copyOfLoop.insert(copyOfLoop.begin() + 3, L"{\n\0");
		copyOfLoop.insert(copyOfLoop.begin() + indexOfSecondLoop + 2, L"}\n\0");
		indexOfSecondLoop += 3;
	}


	isSomething = false;
	for (int i = indexOfSecondLoop + lengthOfSecondLoop; i < copyOfLoop.size() - 1; i++) {
		if (!copyOfLoop[i].empty())
			for (auto& _char : copyOfLoop[i]) {
				if (((_char >= 65) && (_char <= 90)) || ((_char >= 97) && (_char <= 122))) {
					isSomething = true;
					break;
				}

			}
		if (isSomething)
			break;
	}

	if (isSomething) {
		std::wstring ifwstring = L"\t if( t % ( " + nameOfVar2If + L" ) == 0 )\n\0";
		copyOfLoop.insert(copyOfLoop.begin() + indexOfSecondLoop + lengthOfSecondLoop , ifwstring);
		copyOfLoop.insert(copyOfLoop.begin() + indexOfSecondLoop + lengthOfSecondLoop + 1, L"{\n\0");
		copyOfLoop.insert(copyOfLoop.end() - 1, L"}\n\0");
	}

	//indexOfSecondLoop = i;

	mainString.erase(mainString.begin() + indexOfLoop, mainString.begin() + indexOfLoop + loopLength);
	mainString.insert(mainString.begin() + indexOfLoop, copyOfLoop.begin(), copyOfLoop.end());
	return indexOfLoop + copyOfLoop.size();

}

void Parser::ChangeLoops()
{
	int index = 0;
	while (index != -1) {
		index = ChangeLoop(index);
	}


	std::vector<indexPair> indexBlockPosition = FindBlockIndex();
	for (auto& indexes : indexBlockPosition) {
		this->mainString[indexes.first].erase();
		this->mainString[indexes.second].erase();

	}

}

void Parser::AddJunks(int amountOfVariables, int amountOfJunk)
{
	Junker* junker = new Junker(&mainString, &variables);
	junker->FindJunkPlace(amountOfVariables, amountOfJunk);
	delete junker;
}

void Parser::AddEncryption(bool toFile, bool onlyFors, bool isTpm)
{
	Encryption* encryption = new Encryption(&mainString);
	encryption->MakeEncryption(toFile, onlyFors, isTpm);
	delete encryption;
}
