#include "Xor.hpp"

XorerTask(Encrypt, Data, key)

    for (int i = 0, K = i % key.size(); i < Data.size(); i++)
        output.push_back((((Data[i] xor key[K]) xor i xor K) xor (key[K])) + key[K]);
ENDXorTask;

XorerTask(Decrypt, Data, key)

    for (int i = 0, K = i % key.size(); i < Data.size(); i++)
        output.push_back((((Data[i] - key[K]) xor K xor i) xor key[K]) xor (key[K]));
ENDXorTask;

Task(EncryptFile,SE)
{
    string fileName=SE->GetNextArg();
    string Key=SE->GetNextArg();
    ifstream F(fileName);
    stringstream ss;
    ss<<F.rdbuf();
    string Encrypted=Xorer::Encrypt(ss.str(),Key);
    F.close();
    ofstream Fs(fileName+"_XR");
    Fs<<Encrypted;
    Fs.close();
}
Task(DEncryptFile,SE)
{
    string fileName=SE->GetNextArg();
    string Key=SE->GetNextArg();
    ifstream F(fileName);
    stringstream ss;
    ss<<F.rdbuf();
    string DEncrypted=Xorer::Decrypt(ss.str(),Key);
    F.close();
    ofstream Fs(fileName+"U_XR");
    Fs<<DEncrypted;
    Fs.close();
}
    __Register(XOR,SE){
        SE->Register("xor+",&EncryptFile);
        SE->Register("xor-",&DEncryptFile);
    }