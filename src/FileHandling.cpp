#include "FileHandling.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <codecvt>

FileHandling::FileHandling()
{
}

FileHandling::FileHandling(std::string fileName)
{
	void(LoadFile(fileName));
}

FileHandling::~FileHandling()
{
	Clear();
}

std::vector<std::wstring> *FileHandling::LoadFile(std::string fileName)
{
	std::wifstream file(fileName);
	if (!checkExtension(fileName))
	{
		return &this->fileContent;
	}
	std::wstring line;
	if (file.is_open())
	{
		while (std::getline(file, line))
		{
			line += L"\n";
			fileContent.push_back(line);
		}
		file.close();

		deleteArtefacts();
	}

	return &this->fileContent;
}

std::vector<std::wstring> *FileHandling::GetContent()
{
	return &fileContent;
}

bool FileHandling::SaveFile(std::string fileName)
{

	std::locale loc(std::locale(), new std::codecvt_utf8_utf16<wchar_t>);
	std::basic_ofstream<wchar_t> ofs(fileName);
	ofs.imbue(loc);
	std::wofstream file(fileName);
	if (file.is_open())
	{
		for (const auto &line : fileContent)
			ofs << line << std::flush;
		file.close();
		return true;
	}
	return false;
}

bool FileHandling::IsOpen()
{
	return !fileContent.empty();
}

void FileHandling::Clear()
{
	fileContent.clear();
}

bool FileHandling::checkExtension(std::string fileName)
{
	std::string extension = fileName.substr(fileName.find_last_of(".") + 1);
	if (extension != "cpp" && extension != "h" && extension != "hpp" && extension != "c")
		return false;
	return true;
}

void FileHandling::deleteArtefacts()
{
	// Deleting character set, which sometimes generate at start of file
	if (!fileContent[0].empty())
	{
		fileContent[0].erase(0, 3);
		//does not work for some unkown reason
		// auto index = fileContent[0].find(L"ï»¿");
		// if (index != std::wstring::npos){
		// 	fileContent[0].erase(index, 3);
		// 	}
		// index = fileContent[0].find(L"∩╗┐");
		// if (index != std::wstring::npos)
		// {
		// 	fileContent[0].erase(index, 3);
		// }
	}
}