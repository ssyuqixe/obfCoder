#pragma once

#include "Functions.h"
#include <vector>
#include <string>

class Encryption
{
private:
	std::vector<std::wstring>* ptr_mainString;
	std::wstring keyStringName;

	int FindPlaceToAddEncryptionFunction(std::vector<std::wstring> cont);
	void AddFunctionEncryption(bool toFile = false, bool onlyFors = true);
	void EncryptValue(std::wstring value, unsigned char* key, int index, std::wstring decryptStringName, int replaceIndex = 0);
	void AddLibraries(std::vector<std::wstring> libs);
	//std::string RandomKey(int length = 32, bool addDigits = true);
public:
	Encryption(std::vector<std::wstring>* mainString) : ptr_mainString(mainString) {
		keyStringName = RandomUnicode(4, 0x0061, 0x007A) + RandomUnicode(4, 0x0030, 0x0039);
	}
	std::string RandomKey(int length = 32, bool addDigits = true);
	void MakeEncryption(bool toFile, bool onlyFors);
};

