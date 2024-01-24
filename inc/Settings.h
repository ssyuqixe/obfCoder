#ifndef SETTINGS_H
#define SETTINGS_H

#include <QtWidgets/QMainWindow>
#include <string>
namespace settings {
	extern QString inFileName;
	extern QString outFileName;
	extern std::string outPath;
	extern int countOfSettings;
	extern std::vector<int> junkerOptions;
}

#endif // !SETTINGS_H
