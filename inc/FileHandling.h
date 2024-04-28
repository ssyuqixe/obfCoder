#ifndef FILEHANDLING_H
#define FILEHANDLING_H

#include "Functions.h"
#include <iostream>
#include <vector>
#include <string>


class FileHandling
{
private:
	std::string m_path;
	std::vector<std::wstring> m_fileContent;
	bool checkExtension(std::string fileName);
	void deleteArtefacts();
public:
	FileHandling();
	FileHandling(std::string fileName);
	~FileHandling();

	std::vector<std::wstring>* LoadFile(std::string fileName);
	void ReloadFile();
	void SetPath(std::string path) { m_path = path; }
	std::string GetPath() { return m_path; }
	std::vector<std::wstring>* GetContent();
	bool SaveFile(std::string fileName);
	bool IsOpen();
	void Clear();
};

#endif // FILEHANDLING_H