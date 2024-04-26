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
	LoadFile(fileName);
}

std::vector<std::wstring>* FileHandling::LoadFile(std::string fileName)
{
	std::wifstream file(fileName);

	std::wstring line;
	// std::unique_ptr<std::vector<std::wstring>> fileContent = std::make_unique<std::vector<std::wstring>>();
	// this->fileContent = std::move(fileContent);
	if (file.is_open())
	{
		while (std::getline(file, line))
		{
			line += L"\n";
			fileContent.push_back(line);
		}
		file.close();
		
		// Deleting character set, which sometimes generate at start of file
		// Need to fix it
		if (!fileContent[0].empty() && fileContent[0].find(L"ï»¿") != std::wstring::npos)
			fileContent[0].erase(fileContent[0].find(L"ï»¿"), 3);
	}
	else
	{
		//Change this later
		throw std::runtime_error("File not found");
	}
	return &this->fileContent;
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

