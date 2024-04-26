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
public:
	FileHandling();
	FileHandling(std::string fileName);
	~FileHandling() = default;

	std::vector<std::wstring>* LoadFile(std::string fileName);
	bool SaveFile(std::string fileName);

};

#endif // FILEHANDLING_H