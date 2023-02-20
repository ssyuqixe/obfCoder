
#include "stdafx.h"
#include "TPM.h"
#include "TpmConfig.h"
#include <fstream>
#include <locale>
#include <string>
#include <codecvt>  
#include <random>

#define null {}
#define encryptSize 512

void CleanHandlesOfType(Tpm2& tpm, TPM_HT handleType, UINT32 rangeBegin = 0, UINT32 rangeEnd = 0x00FFFFFF)
{
    UINT32  startHandle = (handleType << 24) + rangeBegin,
        rangeSize = rangeEnd - rangeBegin;
    GetCapabilityResponse resp;
    size_t count = 0;
    for (;;)
    {
        resp = tpm.GetCapability(TPM_CAP::HANDLES, startHandle, rangeSize);
        auto handles = dynamic_cast<TPML_HANDLE*>(&*resp.capabilityData)->handle;

        for (auto& h : handles)
        {
            if ((h.handle & 0x00FFFFFF) >= rangeEnd)
                break;
            if (handleType == TPM_HT::NV_INDEX)
            {
                tpm._AllowErrors().NV_UndefineSpace(TPM_RH::OWNER, h);
                if (!tpm._LastCommandSucceeded())
                    fprintf(stderr, "Failed to clean NV index 0x%08X: error %s\n", h.handle, EnumToStr(tpm._GetLastResponseCode()).c_str());
            }
            else if (handleType == TPM_HT::PERSISTENT)
            {
                tpm._AllowErrors().EvictControl(TPM_RH::OWNER, h, h);
                if (!tpm._LastCommandSucceeded())
                    fprintf(stderr, "Failed to clean persistent object 0x%08X: error %s\n", h.handle, EnumToStr(tpm._GetLastResponseCode()).c_str());
            }
            else
                tpm._AllowErrors().FlushContext(h);
            ++count;
        }

        if (!resp.moreData)
            break;
        auto newStart = (UINT32)handles.back().handle + 1;
        rangeSize -= newStart - startHandle;
        startHandle = newStart;
    }

    if (count)
        cout << "Cleaned " << count << " dangling " << EnumToStr(handleType) << " handle" << (count == 1 ? "" : "s") << endl;
    else
        cout << "No dangling " << EnumToStr(handleType) << " handles" << endl;
}

TPM::TPM() {

    device = UseSimulator ? new TpmTcpDevice("127.0.0.1", 2321)
        : (TpmDevice*)new TpmTbsDevice();

    if (!device || !device->Connect())
    {
        device = nullptr;
        throw runtime_error("Could not connect to TPM device.");
    }

    tpm._SetDevice(*device);

    if (UseSimulator)
    {
        // This code is normally not needed for a system/platform TPM.
        assert(device->PlatformAvailable() && device->ImplementsPhysicalPresence() &&
            device->PowerCtlAvailable() && device->LocalityCtlAvailable());

        device->PowerCycle();

        // Startup the TPM
        tpm.Startup(TPM_SU::CLEAR);
    }

    // If the simulator was not shut down cleanly ("disorderly shutdown") or a TPM app
    // crashed midway or has bugs the TPM may go into lockout or have objects abandoned
    // in its (limited) internal memory. Try to clean up and recover the TPM.
    RecoverTpm();

    // Install callbacks to collect command execution statistics.
    StartCallbacks();

    TpmConfig::Init(tpm);


}

TPM::~TPM() {
    if (UseSimulator)
    {
        // A clean shutdown results in fewer lockout errors.
        tpm.Shutdown(TPM_SU::CLEAR);
        device->PowerOff();
    }

    // The following routine finalizes and prints the function stats.
    FinishCallbacks();
    delete inPublic_decrypt, prim_decrypt, aesKey_decrypt, aesHandle_decrypt;
    delete device;
}

string intToHexString(int intValue) {

    string hexStr;

    /// integer value to hex-string
    std::stringstream sstream;
    sstream << "0x"
        << std::setfill('0') << std::setw(1)
        << std::hex << (int)intValue;

    hexStr = sstream.str();
    sstream.clear();    //clears out the stream-string

    return hexStr;
}

void TPM::ArrayParameters()
{
    // Get 20 random bytes from the TPM
    ByteVec rand = tpm.GetRandom(20);
    cout << "Random bytes: " << rand << endl;
    
    outputString = "";
    for (int i = 0; i < rand.size(); i++) {
        outputString += intToHexString(rand[i]) + " ";
    }


    // Get random data from the (default) OS random-number generator and
    // add it to the TPM entropy pool.
    ByteVec osRand = Helpers::RandomBytes(20);
    tpm.StirRandom(osRand);
}



void TPM::RecoverTpm()
{
    tpm._AllowErrors()
        .DictionaryAttackLockReset(TPM_RH::LOCKOUT);

    if (!tpm._LastCommandSucceeded() && UseSimulator)
    {
        tpm._AllowErrors()
            .Shutdown(TPM_SU::CLEAR);

        // If this is a simulator, power-cycle it and clear just to be sure...
        device->PowerCycle();
        tpm.Startup(TPM_SU::CLEAR);

        // Clearing the TPM:
        // - Deletes persistent and transient objects in the Storage and Endorsement hierarchies;
        // - Deletes non-platform NV indices;
        // - Generates new Storage Primary Seed;
        // - Re-enables disabled hierarchies;
        // - Resets Owner, Endorsement, and Lockout auth values and auth policies;
        // - Resets clock, reset and restart counters.
        tpm.Clear(TPM_RH::PLATFORM);
    }

    CleanHandlesOfType(tpm, TPM_HT::LOADED_SESSION);
    CleanHandlesOfType(tpm, TPM_HT::TRANSIENT);
    CleanHandlesOfType(tpm, TPM_HT::PERSISTENT, PersRangeBegin, PersRangeEnd);
    CleanHandlesOfType(tpm, TPM_HT::NV_INDEX, NvRangeBegin, NvRangeEnd);
}

void TPM::Announce(const char* testName)
{
    //SetColor(0);
    //cout << endl;
    //cout << "================================================================================" << endl;
    //cout << "        " << testName << endl;
    //cout << "================================================================================" << endl;
    //cout << endl << flush;
    //SetColor(1);
}


void TPM::StartCallbacks()
{
    //Announce("Installing callback");

    // Install a callback that is invoked after the TPM command has been executed
    tpm._SetResponseCallback(&TPM::TpmCallbackStatic, this);
}

void TPM::FinishCallbacks()
{
   // Announce("Processing callback data");

    //cout << "Commands invoked:" << endl;
    //for (auto it = commandsInvoked.begin(); it != commandsInvoked.end(); ++it)
       // cout << dec << setfill(' ') << setw(32) << EnumToStr(it->first) << ": count = " << it->second << endl;

    //cout << endl << "Responses received:" << endl;
    //for (auto it = responses.begin(); it != responses.end(); ++it)
       // cout << dec << setfill(' ') << setw(32) << EnumToStr(it->first) << ": count = " << it->second << endl;

    /*
    cout << endl << "Commands not exercised:" << endl;
    for (auto it = commandsImplemented.begin(); it != commandsImplemented.end(); ++it)
    {
        if (commandsInvoked.find(*it) == commandsInvoked.end())
            cout << dec << setfill(' ') << setw(1) << EnumToStr(*it) << " ";
    }
    cout << endl;
    */
    tpm._SetResponseCallback(NULL, NULL);
}

void TPM::TpmCallback(const ByteVec& command, const ByteVec& response)
{
    // Extract the command and responses codes from the buffers.
    // Both are 4 bytes long starting at byte 6
    UINT32* commandCodePtr = (UINT32*)&command[6];
    UINT32* responseCodePtr = (UINT32*)&response[6];

    TPM_CC cmdCode = (TPM_CC)ntohl(*commandCodePtr);
    TPM_RC rcCode = (TPM_RC)ntohl(*responseCodePtr);

    // Strip any parameter decorations
    rcCode = Tpm2::ResponseCodeFromTpmError(rcCode);

    commandsInvoked[cmdCode]++;
    responses[rcCode]++;
}

TPM_HANDLE TPM::MakeStoragePrimary(AUTH_SESSION* sess)
{
    TPMT_PUBLIC storagePrimaryTemplate(TPM_ALG_ID::SHA1,
        TPMA_OBJECT::decrypt | TPMA_OBJECT::restricted
        | TPMA_OBJECT::fixedParent | TPMA_OBJECT::fixedTPM
        | TPMA_OBJECT::sensitiveDataOrigin | TPMA_OBJECT::userWithAuth,
        null,           // No policy
        TPMS_RSA_PARMS(Aes128Cfb, TPMS_NULL_ASYM_SCHEME(), 2048, 65537),
        TPM2B_PUBLIC_KEY_RSA());
    // Create the key
    if (sess)
        tpm[*sess];
    return tpm.CreatePrimary(TPM_RH::OWNER, null, storagePrimaryTemplate, null, null)
        .handle;
}

BYTE converterFromString(unsigned char byte1, unsigned char byte2) {
    BYTE value = 0;
    if (byte1 >= '0' && byte1 <= '9')
        value = (byte1 - '0') * 16;
    else
        value = (byte1 - 'a' + 10) * 16;

    if (byte2 >= '0' && byte2 <= '9')
        value += (byte2 - '0');
    else
        value += (byte2 - 'a' + 10);

    return value;
}

void TPM::decryptInit() {
    prim_decrypt = new TPM_HANDLE();
    *prim_decrypt = MakeStoragePrimary();
    inPublic_decrypt = new TPMT_PUBLIC(TPM_ALG_ID::SHA256,
        TPMA_OBJECT::decrypt | TPMA_OBJECT::sign | TPMA_OBJECT::userWithAuth
        | TPMA_OBJECT::sensitiveDataOrigin,
        null,
        TPMS_SYMCIPHER_PARMS(Aes128Cfb),
        TPM2B_DIGEST_SYMCIPHER());
    aesKey_decrypt = new CreateResponse();
    *aesKey_decrypt = tpm.Create(*prim_decrypt, null, *inPublic_decrypt, null, null);
    
    std::string line;
    std::ifstream myfile("TPM_Variables_Key.txt");
    std::string keyString = "";
    if (myfile.is_open())
    {
        while (getline(myfile, line))
        {
            keyString += line;
        }
        myfile.close();
    }
    else {
        throw;
    }

    size_t index;
    while (keyString.find(' ') != std::string::npos)
    {
        index = keyString.find(' ', 0);
        keyString.replace(index, 1, "");
    }
    ByteVec keyBuffer;
    for (int i = 0; i < keyString.size(); i += 2) {
        keyBuffer.push_back(converterFromString(keyString[i], keyString[i + 1]));
    }

    aesKey_decrypt->initFromBytes(keyBuffer);
    aesHandle_decrypt = new TPM_HANDLE();
    *aesHandle_decrypt = tpm.Load(*prim_decrypt, aesKey_decrypt->outPrivate, aesKey_decrypt->outPublic);

}

ByteVec TPM::TPM_decrypt(std::string encryptedText) {
    ByteVec encrypted;
    ByteVec decoded;

    if (prim_decrypt == nullptr)
        decryptInit();

    for (int i = 0; i < encryptedText.length(); i += 2) {
        encrypted.push_back(converterFromString(encryptedText[i], encryptedText[i + 1]));
    }
    ByteVec iv(16);

    auto decrypted = tpm.EncryptDecrypt(*aesHandle_decrypt, (BYTE)1, TPM_ALG_ID::CFB, iv, encrypted);


    return decrypted.outData;
}