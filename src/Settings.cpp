#include "Settings.h"
namespace settings {
	QString inFileName = "notSelected";
	QString outFileName = "notSelected";
	std::string outPath = "notSelected";
	int countOfSettings = 0;
	std::vector<bool> junkerOptions(7, true);	
	std::vector<std::wstring> special_operators{ L"+=", L"-=", L"*=", L"/=", L"<=",L">=",L"++", L"--", L"!=", L"//", L"<<", L">>", L"**", L"->", L"||" };
	std::vector<std::wstring> operators{ L"=",L"+", L"-", L"/", L"*", L"%", L"&", L"<", L">", L"^", L"!", L"?", L",", L"." }; 
	unsigned short rangeOfUnicode[2] = {0x4E00, 0x9FFF};

}