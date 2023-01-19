#include "Settings.h"
namespace settings {
	QString inFileName = "notSelected";
	QString outFileName = "notSelected";
	QString inTPMFile = "notSelected";
	std::string outPath = "notSelected";
	int countOfSettings = 0;
	std::vector<int> junkerOptions = { 1, 2, 3, 4, 5, 6, 7};
	bool isTPMOn = true;
	std::string TPM_Messages = "";
}