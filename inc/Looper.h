#ifndef LOOPER_H
#define LOOPER_H
#include "Functions.h"
#include "Component.h"

class Looper : public Component
{
	std::vector<std::wstring>* p_ContentFile;

    //todo: delete later to get it from Parser class
    //or bring to Functions.h (prob not)
	std::vector<indexPair> FindBlockIndex();
    
	std::wstring startBlock = L"#define obf_block_start";
	std::wstring endBlock = L"#define obf_block_end";

    int ChangeLoop(int indexLoop);
	int FindForLoop(int startIndex);
	int LengthOfLoop(int startIndex);
    int LengthOfSecondLoop(int startIndex, std::vector<std::wstring> wstringTab);
	void GetVariablesFromFor(std::wstring lineFor, std::wstring* tab, short index, wchar_t _char);
	int GetNameForChangeLoop(std::wstring lineLoop, std::wstring lineLoopSecond, std::wstring& nameOfVar);
	void RemoveBracketOfSecondLoop(int startIndex, int loopLength, std::vector<std::wstring>& wstringTab);

public:
    Looper(std::vector<std::wstring>* mainString) : p_ContentFile(mainString) {}


    bool Update(std::vector<int> &settings) override;
    bool DoTechnique() override;
};

#endif // LOOPER_H