
#include "stdafx.h"
#include "TPM.h"
#include "TpmConfig.h"
#include <fstream>
#include <locale>
#include <string>
#include <codecvt>  
#include <random>
#include "Functions.h"

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
    cout << endl;
    cout << "================================================================================" << endl;
    cout << "        " << testName << endl;
    cout << "================================================================================" << endl;
    cout << endl << flush;
    //SetColor(1);
}


void TPM::StartCallbacks()
{
    Announce("Installing callback");

    // Install a callback that is invoked after the TPM command has been executed
    tpm._SetResponseCallback(&TPM::TpmCallbackStatic, this);
}

void TPM::FinishCallbacks()
{
    Announce("Processing callback data");

    cout << "Commands invoked:" << endl;
    for (auto it = commandsInvoked.begin(); it != commandsInvoked.end(); ++it)
        cout << dec << setfill(' ') << setw(32) << EnumToStr(it->first) << ": count = " << it->second << endl;

    cout << endl << "Responses received:" << endl;
    for (auto it = responses.begin(); it != responses.end(); ++it)
        cout << dec << setfill(' ') << setw(32) << EnumToStr(it->first) << ": count = " << it->second << endl;

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


std::string TPM::getOutputString() {
    return outputString;
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

void TPM::EncryptDecryptSample()
{

    TPM_HANDLE prim = MakeStoragePrimary();

    // Make an AES key
    TPMT_PUBLIC inPublic(TPM_ALG_ID::SHA256,
        TPMA_OBJECT::decrypt | TPMA_OBJECT::sign | TPMA_OBJECT::userWithAuth
        | TPMA_OBJECT::sensitiveDataOrigin,
        null,
        TPMS_SYMCIPHER_PARMS(Aes128Cfb),
        TPM2B_DIGEST_SYMCIPHER());

    auto aesKey = tpm.Create(prim, null, inPublic, null, null);

    TPM_HANDLE aesHandle = tpm.Load(prim, aesKey.outPrivate, aesKey.outPublic);

    ByteVec toEncrypt{ 1, 2, 3, 4, 5, 4, 3, 2, 12, 3, 4, 5 };
    ByteVec iv(16);

    auto encrypted = tpm.EncryptDecrypt(aesHandle, (BYTE)0, TPM_ALG_ID::CFB, iv, toEncrypt);
    auto decrypted = tpm.EncryptDecrypt(aesHandle, (BYTE)1, TPM_ALG_ID::CFB, iv, encrypted.outData);


    std::stringstream buffer_string;
    buffer_string << "AES encryption" << endl <<
        "key private: " << aesKey.outPrivate.buffer << endl <<
        "key public: " << aesKey.outPublic.asTpm2B() << endl <<
        "in:  " << toEncrypt << endl <<
        "enc: " << encrypted.outData << endl <<
        "dec: " << decrypted.outData << endl;

    outputString = "";

    outputString = buffer_string.str();

    _ASSERT(decrypted.outData == toEncrypt);

    tpm.FlushContext(prim);
    tpm.FlushContext(aesHandle);
} // EncryptDecryptSample()

std::string TPM::EncryptWholeFile(std::wstring nameOfFile, std::string outPath) {

    TPM_HANDLE prim = MakeStoragePrimary();

    // Make an AES key
    TPMT_PUBLIC inPublic(TPM_ALG_ID::SHA256,
        TPMA_OBJECT::decrypt | TPMA_OBJECT::sign | TPMA_OBJECT::userWithAuth
        | TPMA_OBJECT::sensitiveDataOrigin,
        null,
        TPMS_SYMCIPHER_PARMS(Aes128Cfb),
        TPM2B_DIGEST_SYMCIPHER());

    auto aesKey = tpm.Create(prim, null, inPublic, null, null);

    TPM_HANDLE aesHandle = tpm.Load(prim, aesKey.outPrivate, aesKey.outPublic);


    ByteVec toEncrypt;
    std::wstring_convert<std::codecvt_utf8<wchar_t>> conv1;
    std::wstring u8str = nameOfFile;


    auto u8strSize = u8str.length();
    std::stringstream buffer_string;
    size_t loopsCounter = u8strSize / encryptSize;
    ByteVec iv(16);
    for (int i = 0; i < loopsCounter; i++) {
        toEncrypt.clear();
        for (int j = i * encryptSize; j < (i + 1) * encryptSize; j++) {
                toEncrypt.push_back((u8str[j] & 0xFF00)>>2);
                toEncrypt.push_back(u8str[j] & 0x00FF);
        }
        auto encrypted = tpm.EncryptDecrypt(aesHandle, (BYTE)0, TPM_ALG_ID::CFB, iv, toEncrypt);
        buffer_string << encrypted.outData;
    }

    if (u8strSize % encryptSize) {
        toEncrypt.clear();
        for (int i = loopsCounter * encryptSize; i < u8strSize; i++) {
            toEncrypt.push_back((u8str[i] & 0xFF00) >> 2);
            toEncrypt.push_back(u8str[i] & 0x00FF);
        }
        auto encrypted = tpm.EncryptDecrypt(aesHandle, (BYTE)0, TPM_ALG_ID::CFB, iv, toEncrypt);
        buffer_string << encrypted.outData;
    }




    std::string encryptFile = buffer_string.str();
    /*
    buffer_string << "AES encryption" << endl <<
        "key private: " << aesKey.outPrivate.buffer << endl <<
        "key public: " << aesKey.outPublic.asTpm2B() << endl <<
        "in:  " << toEncrypt << endl <<
        "enc: " << encrypted.outData;
*/
    outputString = "";

    //outputString = buffer_string.str();

    std::ofstream outFile(settings::outPath + "/TPM_Key.txt");
    outFile << aesKey.toBytes();
    outFile.close();

    tpm.FlushContext(prim);
    tpm.FlushContext(aesHandle);

    return encryptFile;
} // EncryptDecryptSample()

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

std::wstring TPM::DecryptWholeFile(std::wstring encryptedFile, std::string keyFile, std::string outPath) {

    std::wstring returnString = encryptedFile;

    
    TPM_HANDLE prim = MakeStoragePrimary();

    
    // Make an AES key
    TPMT_PUBLIC inPublic(TPM_ALG_ID::SHA256,
        TPMA_OBJECT::decrypt | TPMA_OBJECT::sign | TPMA_OBJECT::userWithAuth
        | TPMA_OBJECT::sensitiveDataOrigin,
        null,
        TPMS_SYMCIPHER_PARMS(Aes128Cfb),
        TPM2B_DIGEST_SYMCIPHER());
    
    auto aesKey = tpm.Create(prim, null, inPublic, null, null);
    size_t index;
    while (encryptedFile.find(' ') != std::string::npos)
    {
        index = encryptedFile.find(' ', 0);
        encryptedFile.replace(index, 1, L"");
    }

    while (keyFile.find(' ') != std::string::npos)
    {
        index = keyFile.find(' ', 0);
        keyFile.replace(index, 1, "");
    }

    std::wstring_convert<std::codecvt_utf8<wchar_t>> conv1;
    std::wstring u8str = encryptedFile;

    ByteVec keyBuffer;
    for (int i = 0; i < keyFile.size(); i+=2) {
        //BYTE test = converterFromString(keyFile[i], keyFile[i + 1]);
        //std::cout << keyFile[i] << keyFile[i + 1] << "==" << test << "   or   ";
        //printf("%u\n", test);
        keyBuffer.push_back(converterFromString(keyFile[i], keyFile[i+1]));
    }
    aesKey.initFromBytes(keyBuffer);
    //std::cout << aesKey.toBytes() << std::endl;
    TPM_HANDLE aesHandle = tpm.Load(prim, aesKey.outPrivate, aesKey.outPublic);
    ByteVec iv(16);

    ByteVec encryptedData;
    auto encryptedFileSize = u8str.length();
    std::stringstream wbuffer_string;
    for (int i = 0; i < u8str.size(); i += 2) {
        encryptedData.push_back(converterFromString(u8str[i], u8str[i + 1]));
    }

    ByteVec allDecryptedData; //increase size later, for speed up
    size_t loopsCounter = encryptedFileSize / (encryptSize*4);
    for (int i = 0; i < loopsCounter; i++) {
        encryptedData.clear();
        for (int j = i * (encryptSize*4); j < (i + 1) * (encryptSize*4); j+=2) {
            encryptedData.push_back(converterFromString(u8str[j], u8str[j + 1]));
        }
        auto decrypted = tpm.EncryptDecrypt(aesHandle, (BYTE)1, TPM_ALG_ID::CFB, iv, encryptedData);
        for (int k = 0; k < decrypted.outData.size(); k++)
            allDecryptedData.push_back(decrypted.outData.at(k));
    }
    
    if (encryptedFileSize % (encryptSize * 4)) {
        encryptedData.clear();
        for (int i = loopsCounter * (encryptSize * 4); i < encryptedFileSize; i+=2) {
            encryptedData.push_back(converterFromString(u8str[i], u8str[i+1]));
        }
        auto decrypted = tpm.EncryptDecrypt(aesHandle, (BYTE)1, TPM_ALG_ID::CFB, iv, encryptedData);
        for (int k = 0; k < decrypted.outData.size(); k++)
            allDecryptedData.push_back(decrypted.outData.at(k));
    }
    std::wstring decryptedString;
    for (int i = 0; i < allDecryptedData.size(); i += 2) {
        wchar_t letter = 0x0000;
        letter = (letter | allDecryptedData[i]) << 2;
        letter = (letter | allDecryptedData[i + 1]);
        decryptedString += letter;
    }


    std::wofstream woutFile(outPath);
    woutFile << decryptedString;
    woutFile.close();
    
    tpm.FlushContext(prim);
    tpm.FlushContext(aesHandle);

    return (L"File decrypted succesfull!");
}

static std::mt19937_64 random;

void TPM::EncryptVariables(std::vector<std::wstring>* ptr_string) {
    std::vector<std::wstring> cont{ L"int", L"double", L"float", L"string", L"uint8_t", L"uint16_t", L"uint32_t", L"uint64_t", L"int8_t", L"int16_t", L"int32_t", L"int64_t", L"char", L"char16_t", L"char32_t", L"bool", L"short", L"wchar_t", L"size_t", L"void", L"class", L"struct", L"template", L"namespace" }; //L"void"

    TPM_HANDLE prim = MakeStoragePrimary();

    // Make an AES key
    TPMT_PUBLIC inPublic(TPM_ALG_ID::SHA256,
        TPMA_OBJECT::decrypt | TPMA_OBJECT::sign | TPMA_OBJECT::userWithAuth
        | TPMA_OBJECT::sensitiveDataOrigin,
        null,
        TPMS_SYMCIPHER_PARMS(Aes128Cfb),
        TPM2B_DIGEST_SYMCIPHER());

    auto aesKey = tpm.Create(prim, null, inPublic, null, null);

    TPM_HANDLE aesHandle = tpm.Load(prim, aesKey.outPrivate, aesKey.outPublic);

    std::ofstream outFile(settings::outPath + "/TPM_Variables_Key.txt");
    outFile << aesKey.toBytes();
    outFile.close();

    //find function for place
    int indexToPlaceMainDeFunc = -1;
    for (int i = 0; i < ptr_string->size(); i++) {

        if (!ptr_string->at(i).empty() && ptr_string->at(i).find(L'#') == std::wstring::npos)
            for (auto const& element : cont) {
                if (ptr_string->at(i).find(element) != std::wstring::npos) {
                    indexToPlaceMainDeFunc = i;
                    break;
                }
            }
        if (indexToPlaceMainDeFunc >= 0)
            break;

    }

    if (indexToPlaceMainDeFunc == -1)
        throw;

    std::vector<std::wstring>namesInTemplate;
    /*
    valueFunctionName  | namesInTemplate[0]
    randomcounterName  | namesInTemplate[1]
    dec_keyName		   | namesInTemplate[2]
    decryptedArrayName | namesInTemplate[3]
    valueEndName       | namesInTemplate[4]
    decShortcutName    | namesInTemplate[5]
    */
    for (int i = 0; i < 6; i++)
        namesInTemplate.push_back(RandomUnicode(5, 0x0061, 0x007A) + RandomUnicode(3, 0x0030, 0x0039));

    for (int i = 0; i < namesInTemplate.size(); i++)
        for (int j = 0; j < namesInTemplate.size(); j++) {
            if (i == j)
                continue;
            if (namesInTemplate[i].compare(namesInTemplate[j]) == 0) {
                namesInTemplate[j] = RandomUnicode(5, 0x0061, 0x007A) + RandomUnicode(3, 0x0030, 0x0039);
                i = 0;
                break;
            }
        }

    std::wstring decryptStringName = RandomUnicode(5, 0x0061, 0x007A) + RandomUnicode(3, 0x0030, 0x0039);
    std::wstring functionHeader = L"int " + decryptStringName + L"(std::string " + namesInTemplate[0] + L", int " + namesInTemplate[1] + L") \n{\n\0";
    std::wstring functionBody1 = L"if (tpm == nullptr) {tpm = new TPM(); } ByteVec decoded = tpm->TPM_decrypt("+ namesInTemplate[0] +L"); unsigned char index = 0;\0";
    std::wstring functionBody2 = L"for (int i = 0; i < decoded.size() - 3; i++) {if (decoded[i] == 21 && decoded[i + 1] == 37 && decoded[i + 2] == 24){index = i;break;}}\0";
    std::wstring functionBody3 = L"int value = 0;std::string strValue = \"\";for (unsigned char i = 0; i < index; i++){strValue += decoded[i];}value = std::stoi(strValue);return value - "+ namesInTemplate[1] +L";}\0";

    //this->mainString.insert(mainString.begin() + indexToPlaceMainDeFunc + 0, randomCounter);
    ptr_string->insert(ptr_string->begin() + indexToPlaceMainDeFunc + 0, functionHeader);
    ptr_string->insert(ptr_string->begin() + indexToPlaceMainDeFunc + 1, functionBody1);
    ptr_string->insert(ptr_string->begin() + indexToPlaceMainDeFunc + 2, functionBody2);
    ptr_string->insert(ptr_string->begin() + indexToPlaceMainDeFunc + 3, functionBody3);
    std::wstring keyString = L"TPM* tpm = nullptr;";
    ptr_string->insert(ptr_string->begin() + indexToPlaceMainDeFunc + 0, keyString);


    std::string valueToEnc;

        for (int i = 0; i < ptr_string->size(); i++) {
            if (!ptr_string->empty()) {
                std::vector<std::wstring> container;
                Split(ptr_string->at(i), container, L' ');

                std::locale loc;
                if (i >= indexToPlaceMainDeFunc && i <= indexToPlaceMainDeFunc + 3)
                    continue;
                int replaceIndex = 0;
                for (int element = 0; element < container.size(); element++) {

                    bool isDigit = true;
                    for (int j = 0; j < container[element].length(); j++)
                        if (isdigit(container[element][j], loc) == false) {
                            isDigit = false;
                            break;
                        }

                    if (!container[element].empty() && isDigit == true && element > 0 && (container[element - 1].compare(L"[") != 0 && container[element - 1].compare(L".") != 0) && element < container.size() - 1 && container[element + 1].compare(L".") != 0) {
                        int counter = random() % INT_MAX; //change to tpm random function
                        valueToEnc = std::to_string(std::stoi(container[element]) + counter);
                        ByteVec toEncrypt(valueToEnc.begin(), valueToEnc.end()); //can do faster
                        toEncrypt.push_back((BYTE)21);
                        toEncrypt.push_back((BYTE)37);
                        toEncrypt.push_back((BYTE)24);

                        ByteVec rand = tpm.GetRandom(20);
                        toEncrypt.insert(toEncrypt.end(), rand.begin(), rand.end());

                        ByteVec iv(16);
                        auto encrypted = tpm.EncryptDecrypt(aesHandle, (BYTE)0, TPM_ALG_ID::CFB, iv, toEncrypt);

                        std::vector<indexPair> indexPositions = FindCharIndex(ptr_string->at(i), L"\"", false);

                        std::vector<indexPair> indexPositionByChar = FindCharIndex(ptr_string->at(i), L"'", false);//
                        std::copy(indexPositionByChar.begin(), indexPositionByChar.end(), std::back_inserter(indexPositions));//

                        std::wstring Value = L"";
                        std::wstringstream ss;
                        for (auto& enp : encrypted.outData) {
                            //Value += L"\\x" + std::to_wstring(enp); //L"\\x"+
                            if(enp > 0x0f)
                                ss << std::hex << enp;
                            else
                                ss << std::hex << "0" << enp;
                        }
                        Value = ss.str();

                        if (indexPositions.empty() == true) {
                            std::wstring text = L" " + decryptStringName + L"(\"" + Value + L"\" , " + std::to_wstring(counter) + L" ) ";
                            ptr_string->at(i).replace(ptr_string->at(i).find(L" " + container[element] + L" "), container[element].length() + 2, text);
                        }
                        else {
                            int diff = 0;
                            int position = ptr_string->at(i).find(L" " + container[element] + L" ", diff);
                            while (position != std::wstring::npos) {
                                bool isInside = false;

                                for (int i = 0; i < indexPositions.size(); i++) {
                                    if (position >= indexPositions[i].first && position <= indexPositions[i].second) {
                                        isInside = true;
                                        diff = indexPositions[i].second;
                                        break;
                                    }
                                }

                                if (isInside == false) {
                                    std::wstring text = L" " + decryptStringName + L"(\"" + Value + L"\" , " + std::to_wstring(counter) + L" ) ";
                                    ptr_string->at(i).replace(position, container[element].length() + 2, text);

                                    for (int i = 0; i < indexPositions.size(); i++) {
                                        if (position < indexPositions[i].first) {
                                            indexPositions[i].first += text.length() - (container[element].length() + 2);
                                            indexPositions[i].second += text.length() - (container[element].length() + 2);
                                        }
                                    }

                                    break;
                                }
                                position = ptr_string->at(i).find(L" " + container[element] + L" ", diff);

                            }
                        }

                    }

                }


            }
        }

}