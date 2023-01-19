#pragma once
#include <QtWidgets/QMainWindow>
#include <string>
namespace settings {
	extern QString inFileName;
	extern QString outFileName;
	extern QString inTPMFile;
	extern std::string outPath;
	extern int countOfSettings;
	extern std::vector<int> junkerOptions;
	extern bool isTPMOn;
	extern std::string TPM_Message;
}

