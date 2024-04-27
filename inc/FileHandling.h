#ifndef FILEHANDLING_H
#define FILEHANDLING_H

#include "Functions.h"
#include <iostream>
#include <vector>
#include <string>


class FileHandling
{
private:
	std::vector<std::wstring> fileContent;
	bool checkExtension(std::string fileName);
	void deleteArtefacts();
public:
	FileHandling();
	FileHandling(std::string fileName);
	~FileHandling();

	std::vector<std::wstring>* LoadFile(std::string fileName);
	std::vector<std::wstring>* GetContent();
	bool SaveFile(std::string fileName);
	bool IsOpen();
	void Clear();
};

#endif // FILEHANDLING_H