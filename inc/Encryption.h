#ifndef ENCRYPTION_H
#define ENCRYPTION_H

#include "Functions.h"
#include "Component.h"
#include <vector>
#include <string>

class Encryption : public Component
{
private:
	std::vector<std::wstring>* p_ContentFile;
	std::wstring m_keyVariable;
	bool m_toFile;
	bool m_onlyFors;

	int FindPlaceToAddEncryptionFunction(std::vector<std::wstring> cont);
	void AddFunctionEncryption(bool toFile = false, bool onlyFors = true);
	void EncryptValue(std::wstring value, unsigned char* key, int index, std::wstring decryptStringName, int replaceIndex = 0);
	void AddLibraries(std::vector<std::wstring> libs);
	std::string RandomKey(int length = 32, bool addDigits = true);
public:
	Encryption(std::vector<std::wstring>* mainString) : p_ContentFile(mainString) {
		m_keyVariable = RandomUnicode(4, 0x0061, 0x007A) + RandomUnicode(4, 0x0030, 0x0039);
	}
	void MakeEncryption(bool toFile, bool onlyFors);

	
	bool Update(std::vector<int> &settings) override;
	bool DoTechnique() override;
};

#endif // ENCRYPTION_H