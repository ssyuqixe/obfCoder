#include "pch.h"
#include "..\GUI\Parser.h"
#include "..\GUI\Parser.cpp"
#include "..\GUI\Encryption.h"
#include "..\GUI\Encryption.cpp"
#include "..\GUI\Junker.h"
#include "..\GUI\Junker.cpp"
#include "..\GUI\Settings.h"
#include "..\GUI\Settings.cpp"

TEST(TestCaseName2, TestName2) {

	EXPECT_EQ(1,1);

}


TEST(EncryptionSS, EncryptionSS) {

	Encryption* encryption = new Encryption(nullptr);


	EXPECT_NE("", encryption->RandomKey());
	delete encryption;
}

TEST(TestCaseName, TestName) {

	Parser* parser = new Parser("test_document.cpp");
	std::vector<std::wstring> mainstring = parser->GetMainString();



	EXPECT_EQ(L"#include <iostream>", mainstring[0]);
	delete parser;
}