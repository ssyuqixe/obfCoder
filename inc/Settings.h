#ifndef SETTINGS_H
#define SETTINGS_H

#include <QtWidgets/QMainWindow>
#include <string>
namespace settings {
	extern QString inFileName;
	extern QString outFileName;
	extern std::string outPath;
	extern int countOfSettings;
	extern std::vector<bool> junkerOptions;
	extern std::vector<std::wstring> special_operators;
	extern std::vector<std::wstring> operators;
	extern unsigned short rangeOfUnicode[2];
}

#endif // !SETTINGS_H
