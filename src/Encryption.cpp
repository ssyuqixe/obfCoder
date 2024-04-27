#include "Encryption.h"
#include "Functions.h"
#include "Settings.h"
#include <iostream>
#include <sstream>
#include <fstream>
#include <random>
#include <openssl/aes.h>
#include <openssl/crypto.h>
#include <codecvt>

int Encryption::FindPlaceToAddEncryptionFunction(std::vector<std::wstring> cont)
{
	for (int i = 0; i < ptr_mainString->size(); i++)
		if (!ptr_mainString[i].empty() && ptr_mainString->at(i).find(L'#') == std::wstring::npos)
			for (const auto &element : cont)
				if (ptr_mainString->at(i).find(element) != std::wstring::npos)
					return i;
	return 0;
}

void Encryption::AddFunctionEncryption(bool toFile, bool onlyFors)
{
	std::vector<std::wstring> cont{L"int", L"double", L"float", L"string", L"uint8_t", L"uint16_t", L"uint32_t", L"uint64_t", L"int8_t", L"int16_t", L"int32_t", L"int64_t", L"char", L"char16_t", L"char32_t", L"bool", L"short", L"wchar_t", L"size_t", L"void", L"class", L"struct", L"template", L"namespace"}; // L"void"

	std::string skey = RandomKey();
	std::wstring decryptStringName = RandomUnicode(5, 0x0061, 0x007A) + RandomUnicode(3, 0x0030, 0x0039);

	unsigned char *key = (unsigned char *)skey.c_str();

	for (int i = 0; i < 32; i++)
		std::cout << key[i];
	std::cout << std::endl;

	std::wstring keyString = L"";
	std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
	std::wstring wKey = converter.from_bytes(skey);
	if (toFile == false)
	{
		keyString = L"unsigned char " + keyStringName + L"[] = \"" + wKey + L"\"; \n\0 ";
	}
	else
	{

		// std::locale loc(std::locale(), new std::codecvt_utf8_utf16<wchar_t>);
		// std::basic_ofstream<wchar_t> ofs("key.txt");
		// ofs.imbue(loc);
		std::ofstream ofs;
		ofs.open(settings::outPath + "/key.txt");
		ofs << skey << std::flush;
		ofs.close();

		keyString = L"std::ifstream file(\"key.txt\"); \n std::string str; \n std::getline(file, str); \n unsigned char* " + keyStringName + L" = (unsigned char*)str.c_str(); \n ";
	}

	int indexToPlaceMainDeFunc = FindPlaceToAddEncryptionFunction(cont);
	std::cout << indexToPlaceMainDeFunc << std::endl;

	int indexOfLoop = -1;

	std::vector<std::wstring> namesInTemplate;
	/*
	valueFunctionName  | namesInTemplate[0]
	randomcounterName  | namesInTemplate[1]
	dec_keyName		   | namesInTemplate[2]
	decryptedArrayName | namesInTemplate[3]
	valueEndName       | namesInTemplate[4]
	decShortcutName    | namesInTemplate[5]
	*/
	for (int i = 0; i < 6; i++)
		namesInTemplate.push_back(RandomUnicode(5, 0x0061, 0x007A) + RandomUnicode(3, 0x0030, 0x0039));

	for (int i = 0; i < namesInTemplate.size(); i++)
		for (int j = 0; j < namesInTemplate.size(); j++)
		{
			if (i == j)
				continue;
			if (namesInTemplate[i].compare(namesInTemplate[j]) == 0)
			{
				namesInTemplate[j] = RandomUnicode(5, 0x0061, 0x007A) + RandomUnicode(3, 0x0030, 0x0039);
				i = 0;
				break;
			}
		}

	std::wstring functionHeader = L"int " + decryptStringName + L"(unsigned char* " + namesInTemplate[0] + L", int " + namesInTemplate[1] + L") {\n\0";
	std::wstring functionBody1 = L"AES_KEY " + namesInTemplate[2] + L";\n  unsigned char " + namesInTemplate[3] + L"[80];\n AES_set_decrypt_key(" + keyStringName + L", 128, &" + namesInTemplate[2] + L");\n\0";
	std::wstring functionBody2 = L"	AES_decrypt(" + namesInTemplate[0] + L", " + namesInTemplate[3] + L", &" + namesInTemplate[2] + L");\n\0";
	std::wstring functionBody3 = L"std::string " + namesInTemplate[4] + L"; \n for (const auto& " + namesInTemplate[5] + L" : " + namesInTemplate[3] + L") \n " + namesInTemplate[4] + L" += " + namesInTemplate[5] + L"; \n return stoi(" + namesInTemplate[4] + L") - " + namesInTemplate[1] + L"; }\n\0";

	// this->mainString.insert(mainString.begin() + indexToPlaceMainDeFunc + 0, randomCounter);
	ptr_mainString->insert(ptr_mainString->begin() + indexToPlaceMainDeFunc + 0, functionHeader);
	ptr_mainString->insert(ptr_mainString->begin() + indexToPlaceMainDeFunc + 1, functionBody1);
	ptr_mainString->insert(ptr_mainString->begin() + indexToPlaceMainDeFunc + 2, functionBody2);
	ptr_mainString->insert(ptr_mainString->begin() + indexToPlaceMainDeFunc + 3, functionBody3);
	if (toFile == false)
		ptr_mainString->insert(ptr_mainString->begin() + indexToPlaceMainDeFunc + 0, keyString);
	else
		ptr_mainString->insert(ptr_mainString->begin() + indexToPlaceMainDeFunc + 1, keyString);

	std::string valueToEnc;

	if (onlyFors == true)
		for (int i = 0; i < ptr_mainString->size(); i++)
		{
			if (!ptr_mainString->empty() && ptr_mainString->at(i).find(L"for") != std::wstring::npos)
			{
				std::vector<std::wstring> container;
				std::vector<std::wstring> container2;
				Split(ptr_mainString->at(i), container, L';');
				Split(container.front(), container2, L'=');

				while (container2.back().find(L" ") != std::wstring::npos)
				{
					container2.back().replace(container2.back().find(L" "), 1, L"");
				}
				std::locale loc;

				bool isDigit = true;
				for (int j = 0; j < container2.back().length(); j++)
					if (isdigit(container2.back()[j], loc) == false)
					{
						isDigit = false;
						break;
					}
				if (isDigit == true)
				{
					EncryptValue(container2.back(), key, i, decryptStringName);
				}
			}
		}
	else
		for (int i = 0; i < ptr_mainString->size(); i++)
		{
			if (!ptr_mainString->empty())
			{
				std::vector<std::wstring> container;
				Split(ptr_mainString->at(i), container, L' ');

				std::locale loc;

				int replaceIndex = 0;
				for (int element = 0; element < container.size(); element++)
				{

					bool isDigit = true;
					for (int j = 0; j < container[element].length(); j++)
						if (isdigit(container[element][j], loc) == false)
						{
							isDigit = false;
							break;
						}

					if (!container[element].empty() && isDigit == true && element > 0 && (container[element - 1].compare(L"[") != 0 && container[element - 1].compare(L".") != 0) && element < container.size() - 1 && container[element + 1].compare(L".") != 0)
					{
						EncryptValue(container[element], key, i, decryptStringName);
					}
				}
			}
		}
}

void Encryption::EncryptValue(std::wstring valueCode, unsigned char *key, int index, std::wstring decryptStringName, int replaceIndex)
{
	int counter = randomEngine.gen() % INT_MAX;

	std::string valueToEnc = std::to_string(std::stoi(valueCode) + counter);
	// counter++;
	unsigned char *text = (unsigned char *)valueToEnc.c_str();
	unsigned char enc_out[80];
	AES_KEY enc_key;
	AES_set_encrypt_key(key, 128, &enc_key);
	AES_encrypt(text, enc_out, &enc_key);

	std::vector<indexPair> indexPositions = FindCharIndex(ptr_mainString->at(index), L"\"", false);

	std::vector<indexPair> indexPositionByChar = FindCharIndex(ptr_mainString->at(index), L"'", false);	   //
	std::copy(indexPositionByChar.begin(), indexPositionByChar.end(), std::back_inserter(indexPositions)); //

	std::wstring Value = L"";
	std::wstringstream ss;
	for (auto &enp : enc_out)
	{
		// Value += L"\\x" + std::to_wstring(enp); //L"\\x"+
		ss << L"\\x" << std::hex << (int)enp;
	}
	Value = ss.str();

	if (indexPositions.empty() == true)
	{
		std::wstring text = L" " + decryptStringName + L"((unsigned char*)\"" + Value + L"\" , " + std::to_wstring(counter) + L" ) ";
		ptr_mainString->at(index).replace(ptr_mainString->at(index).find(L" " + valueCode + L" "), valueCode.length() + 2, text);
	}
	else
	{
		int diff = 0;
		int position = (int)(ptr_mainString->at(index).find(L" " + valueCode + L" ", diff));
		while (position != std::wstring::npos)
		{
			bool isInside = false;

			for (int i = 0; i < indexPositions.size(); i++)
			{
				if (position >= indexPositions[i].first && position <= indexPositions[i].second)
				{
					isInside = true;
					diff = (int)(indexPositions[i].second);
					break;
				}
			}

			if (isInside == false)
			{
				std::wstring text = L" " + decryptStringName + L"( (unsigned char *)\"" + Value + L"\" , " + std::to_wstring(counter) + L" ) ";
				ptr_mainString->at(index).replace(position, valueCode.length() + 2, text);

				for (int i = 0; i < indexPositions.size(); i++)
				{
					if (position < indexPositions[i].first)
					{
						int difference = int(text.length() - (valueCode.length() + 2));
						indexPositions[i].first += difference;
						indexPositions[i].second += difference;
					}
				}

				break;
			}
			position = (int)(ptr_mainString->at(index).find(L" " + valueCode + L" ", diff));
		}
	}
}

void Encryption::AddLibraries(std::vector<std::wstring> libs)
{
	int indexOfLastInclude = 0;
	for (int i = 0; i < ptr_mainString->size(); i++)
	{
		if (CheckInclude(ptr_mainString->at(i)) == true)
		{
			indexOfLastInclude = i;
		}
	}

	for (int i = 0; i < indexOfLastInclude; i++)
	{
		if (ptr_mainString->at(i).empty() == false)
		{
			for (auto &lib : libs)
			{
				if (ptr_mainString->at(i).find(lib) != std::wstring::npos)
				{
					lib = L"exist";
				}
			}
		}
	}

	for (auto &lib : libs)
	{
		if (lib.compare(L"exist") != 0)
		{
			ptr_mainString->insert(ptr_mainString->begin() + indexOfLastInclude + 1, L"#include " + lib + L"\n");
		}
	}
}

std::string Encryption::RandomKey(int length, bool addDigits)
{
	unsigned char randomArray[] = "0123456789abcdefghijklmnoprstuvwz";

	std::string key = "";

	for (int i = 0; i < length; i++)
	{
		key += randomArray[randomEngine.gen() % 33];
	}

	return key;
}

void Encryption::MakeEncryption(bool toFile, bool onlyFors)
{
	AddFunctionEncryption(toFile, onlyFors);
	std::vector<std::wstring> vector = {L"<openssl/aes.h>", L"<fstream>", L"<string>"};
	AddLibraries(vector);
}
