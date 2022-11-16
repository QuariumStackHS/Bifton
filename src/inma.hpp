#include <math.h>
#include <iostream>
#include <array>
#include <string.h>
#include <time.h>
#include <ctime>
#include <map>
#include <memory.h>
#include <filesystem>


#include <filesystem>
using namespace std;
using namespace std::filesystem;
using RDI = std::filesystem::recursive_directory_iterator;
#include <string>
#include "Tasks/BCXX/BiftonCxx/Signataire.hpp"
class String : protected SHA1, public string
{
protected:
    const char *B64chars = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

    const int B64index[256] =
        {
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 62, 63, 62, 62, 63,
            52, 53, 54, 55, 56, 57, 58, 59, 60, 61, 0, 0, 0, 0, 0, 0,
            0, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14,
            15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 0, 0, 0, 0, 63,
            0, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40,
            41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51};

    const std::string b64encode(const void *data, const size_t &len)
    {
        std::string result((len + 2) / 3 * 4, '=');
        unsigned char *p = (unsigned char *)data;
        char *str = &result[0];
        size_t j = 0, pad = len % 3;
        const size_t last = len - pad;

        for (size_t i = 0; i < last; i += 3)
        {
            int n = int(p[i]) << 16 | int(p[i + 1]) << 8 | p[i + 2];
            str[j++] = B64chars[n >> 18];
            str[j++] = B64chars[n >> 12 & 0x3F];
            str[j++] = B64chars[n >> 6 & 0x3F];
            str[j++] = B64chars[n & 0x3F];
        }
        if (pad) /// Set padding
        {
            int n = --pad ? int(p[last]) << 8 | p[last + 1] : p[last];
            str[j++] = B64chars[pad ? n >> 10 & 0x3F : n >> 2];
            str[j++] = B64chars[pad ? n >> 4 & 0x03F : n << 4 & 0x3F];
            str[j++] = pad ? B64chars[n << 2 & 0x3F] : '=';
        }
        return result;
    }

    const std::string b64decode(const void *data, const size_t &len)
    {
        if (len == 0)
            return "";

        unsigned char *p = (unsigned char *)data;
        size_t j = 0,
               pad1 = len % 4 || p[len - 1] == '=',
               pad2 = pad1 && (len % 4 > 2 || p[len - 2] != '=');
        const size_t last = (len - pad1) / 4 << 2;
        std::string result(last / 4 * 3 + pad1 + pad2, '\0');
        unsigned char *str = (unsigned char *)&result[0];

        for (size_t i = 0; i < last; i += 4)
        {
            int n = B64index[p[i]] << 18 | B64index[p[i + 1]] << 12 | B64index[p[i + 2]] << 6 | B64index[p[i + 3]];
            str[j++] = n >> 16;
            str[j++] = n >> 8 & 0xFF;
            str[j++] = n & 0xFF;
        }
        if (pad1)
        {
            int n = B64index[p[last]] << 18 | B64index[p[last + 1]] << 12;
            str[j++] = n >> 16;
            if (pad2)
            {
                n |= B64index[p[last + 2]] << 6;
                str[j++] = n >> 8 & 0xFF;
            }
        }
        return result;
    }

public:
    String(string k)
    {
        this->append(k);
    }
    string Hash()
    {
        this->update(*this);
        return this->final();
    }
    String b64encode()
    {
        return b64encode(this->c_str(), this->size());
    }

    String b64decode()
    {
        return b64decode(this->c_str(), this->size());
    }
};

/*
Fname\nContent
*/

void PackThisfile(string fn)
{
    ifstream Fo(fn);

    stringstream ss;
    ss << Fo.rdbuf();
    String C = ss.str();
    ofstream Fi(fn + ".B64");
    Fi << C.b64encode();
    Fo.close();
    Fi.close();
}
void UnPackThisfile(string fn)
{
    ifstream Fo(fn + ".B64");

    stringstream ss;
    ss << Fo.rdbuf();
    String C = ss.str();
    ofstream Fi(fn);
    Fi << C.b64decode();
    Fo.close();
    Fi.close();
}
class Pack
{
public:
    map<String, string> Files;
    vector<String> FileNames;
    vector<int> deleted;
    Pack() {}
    void Append(string Fname, string c)
    {
        FileNames.push_back(Fname);
        Files[Fname] = String(c).b64encode();
    }
    void openPack(string Fname)
    {
        ifstream FileO(Fname);
        stringstream ss;
        ss << FileO.rdbuf();
        String Raw_File(ss.str());
        FileO.close();
        u_int32_t Ptr = 0;
        string buffer = "";
        string buffer0 = "";
        bool S = 0;
        while (Raw_File[Ptr] != '#')
        {
            if (Raw_File[Ptr] == ',')
            {
                buffer0 = buffer;
            }
            else if (Raw_File[Ptr] == '\n')
            {
                FileNames.push_back(buffer0);
                Files[buffer0] = buffer;
                buffer = "";
            }
            else
                buffer.push_back(Raw_File[Ptr]);
            Ptr++;
        }
    }
    bool isdeleted(int A)
    {
        for (int i = 0; i < this->deleted.size(); i++)
            if (this->deleted[i] == A)
                return 1;
        return 0;
    }
    void WritePack(string Fname)
    {
        ofstream FileO(Fname);
        for (int i = 0; i < FileNames.size(); i++)
        {
            if (!isdeleted(i))
                FileO << FileNames[i] << "," << Files[FileNames[i]] << "\n";
        }
        FileO << "#";
        FileO.close();
    }
    void Dump(string Fname)
    {
        ofstream A(Fname);
        A << ((String)Files[Fname]).b64decode();
        A.close();
    }
    void Dump()
    {
        ofstream A;
        for (int i = 0; i < FileNames.size(); i++)
        {
            A.open(FileNames[i]);
            A << ((String)Files[FileNames[i]]).b64decode();
            A.close();
        }
    }
    void remove(string Fname)
    {
        for (int i = 0; i < this->FileNames.size(); i++)
            if (strcmp(Fname.c_str(), this->FileNames[i].c_str()) == 0)
                deleted.push_back(i);
    }
    void list()
    {
        for (int i = 0; i < this->FileNames.size(); i++)
        {
            cout << this->FileNames[i] << " : " << this->Files[this->FileNames[i]].size() << endl;
        }
    }

    /*
    EncodedFname,encodedContent
    */
};
string FileContent(string g)
{
    ifstream As(g);
    stringstream ss;
    ss << As.rdbuf();
    string Ret = ss.str();
    As.close();
    return Ret;
}