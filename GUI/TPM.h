#pragma once

#include "include/Tpm2.h"
#include "Settings.h"

using namespace TpmCpp;
extern bool UseSimulator;
extern bool settings::isTPMOn;
extern string settings::TPM_Message;

// Beginning of the TPM NV indices range used by the samples
constexpr int NvRangeBegin = 2101;
constexpr int NvRangeEnd = 3000;

// Beginning of the TPM persistent objects range used by the samples
constexpr int PersRangeBegin = 2101;
constexpr int PersRangeEnd = 3000;

static const TPMT_SYM_DEF_OBJECT Aes128Cfb{ TPM_ALG_ID::AES, 128, TPM_ALG_ID::CFB };

inline TPM_HANDLE RandomNvHandle()
{
	return TPM_HANDLE::NV(Helpers::RandomInt(NvRangeBegin, NvRangeEnd));
}

inline TPM_HANDLE RandomPersHandle()
{
	return TPM_HANDLE::Persistent(Helpers::RandomInt(PersRangeBegin, PersRangeEnd));
}

class TPM
{
private:

public:
	TPM();
	~TPM();
	void StartCallbacks();
	void ArrayParameters();

	void TpmCallback(const ByteVec& command, const ByteVec& response);

	static void TpmCallbackStatic(const ByteVec& command, const ByteVec& response, void* context)
	{
		static_cast<TPM*>(context)->TpmCallback(command, response);
	}
	std::string getOutputString();
	void FinishCallbacks();
	void EncryptDecryptSample();

	std::string EncryptWholeFile(std::wstring nameOfFile, std::string outPath);
	std::wstring DecryptWholeFile(std::wstring nameOfFile);

	TPM_HANDLE MakeStoragePrimary(AUTH_SESSION* sess = nullptr);

protected:
	std::string outputString;
	void Announce(const char* testName);
	void RecoverTpm();
	_TPMCPP Tpm2 tpm;
	_TPMCPP TpmDevice* device;
	std::map<_TPMCPP TPM_CC, int> commandsInvoked;
	std::map<_TPMCPP TPM_RC, int> responses;
};

