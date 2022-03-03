#include "BiftonCxx.hpp"
#include "Data/Registry.hpp"
//delete next 2 line to stop SHA1 compare
#include "SHA1/SHA1.hpp"
#define PRINTSHA1
// delete ^ if you dont want to see SHA1 output

#include <iomanip>
string FMP(string g) { return string("<") + g + string(">"); }
string FMS(string g) { return string("\"") + g + string("\""); }
Deterministix::Deterministix()
{
    RegisterDet(this);
}
string getCurrentTime()
{
    time_t t = time(0); // get time now
    tm *now = localtime(&t);
    stringstream ss;
    ss << RESET << (now->tm_hour) << ':'
       << (now->tm_min) << ':'
       << now->tm_sec;
    return ss.str();
}
void splitString(vector<string> &FP, string str, string delimiter = " ")
{
    int start = 0;
    int end = str.find(delimiter);
    while (end != -1)
    {
        FP.push_back(str.substr(start, end - start));
        start = end + delimiter.size();
        end = str.find(delimiter, start);
    }
    FP.push_back(str.substr(start, end - start));
}

string GetFName(string path)
{
    vector<string> Y;
    splitString(Y, path, "/");
    return Y.at(Y.size() - 1);
}
struct FilePath
{
    string Directory = "";
    string FileName = "";
};
FilePath *SplitPath_FileNAme(string g)
{
    vector<string> FP;
    splitString(FP, g, "/");
    struct FilePath *FPV = new FilePath;
    for (int i = 0; i + 1 < FP.size(); i++)
    {
        FPV->Directory.append(FP[i]) += "/";
    }
    FPV->FileName = FP[FP.size() - 1];
    return FPV;
}
bool Compare(char *I, char *J)
{
    for (int i = 0; i < 32; i++)
    {
        if (I[i] != J[i])
            return 0;
    }
    return 1;
}
/*bool Compare(stringstream &FileContain, string Filename)
{
    SHA256 ShaHash = SHA256();
    ShaHash.update(FileContain.str());
    char *ShaCurrentFile = (char *)ShaHash.digest();
    char *ShaOldFile = (char *)ShaHash.digest();
    bool ret = 1;
    if (exists(Filename) && exists(get_c_name(Filename)))
    {
        ifstream f(Filename + ".Checksum");
        stringstream ss;
        f.read(ShaOldFile,32);
        f.close();
        ret = Compare(ShaOldFile,ShaCurrentFile);
        cout << ret << endl;
    }
    else
        ret = 0;
    ofstream f(Filename + ".Checksum");
    f<<ShaCurrentFile;

    return ret;
}*/
bool FindIncludes(stringstream &FileContain, Deterministix *This, string Filename, bool print = 0, bool SHA = 1)
{
    bool ret = 1;
    string C = FileContain.str();
    string Tofind = "#include";
    vector<int> Includes;
    vector<int> Color;
    int BeforeLinenbr = This->LineAprox;
    int BeforeRealLinenbr = This->RealLine;
    int Count = 0;
    bool Skip = 0;
    bool OneLineSkip = 0;
    int IncludesINT = 0;
    int Uninclude = 0;

    // if()
    for (int i = 0; i < C.size(); i++)
    {

        if ((C[i] == '"') || ((C[i] == '/') && (C[i + 1] == '*')) || ((C[i] == '*') && (C[i + 1] == '/')))
            Skip = !Skip;
        if ((C[i] == '/') && (C[i + 1] == '/'))
            OneLineSkip = 1;
        if (C[i] == '\n')
        {
            if (!OneLineSkip && !Skip)
                This->RealLine++;
            This->LineAprox++;
        }
        OneLineSkip = ((C[i] == '\n') && OneLineSkip) ? 0 : OneLineSkip;

        if (!Skip && !OneLineSkip)
        {
            if (Tofind[Count] == C[i])
            {
                Count++;
            }
            else if (Count >= Tofind.size())
            {
                if (print)
                    IncludesINT++;
                if ((C[i + 1] == '"') || (C[i + 2] == '"'))
                {
                    Color.push_back(1);
                    Includes.push_back(i);
                }
                else if ((C[i + 1] == '<') || (C[i + 2] == '<'))
                    Color.push_back(0);
                else
                {
                    Color.push_back(2);
                }
                Count = 0;
            }
            else
                Count = 0;
        }
    }
    int Counta = 0;
    bool init = 0;
    string TempsStr = "";
    struct FilePath *Tempi;
    if (print)
    {
        for (int i = 0; i < Color.size(); i++)
        {
            switch (Color[i])
            {
            case 0:
                cout << YELLOW << ".";
                break;
            case 1:
                cout << BOLDMAGENTA << "?" << RESET;
                break;
            case 2:
                cout << RED << "!";
                break;
            }
        }
        Sizer S = sizetoK(This->LineAprox - BeforeLinenbr);
        Sizer SFE = sizetoK(This->RealLine - BeforeRealLinenbr);
        cout << RESET << GREEN " Done √" << RESET << " Lines of code : " << setprecision(6)
             << MAGENTA << S.data << RESET << BOLDMAGENTA << S.c << RESET << " / " << MAGENTA << SFE.data << RESET << BOLDMAGENTA << SFE.c << RESET
             << " ( " << setprecision(3) << RED << 100 * (((double)This->RealLine - BeforeRealLinenbr) / ((double)This->LineAprox - BeforeLinenbr)) << RESET << "% )" << endl;
    }
    for (int i = 0; i < Includes.size(); i++)
    {
        init = 0;
        Counta = 0;
        TempsStr = "";
#define Ii Includes[i]
#define CIiStartPlus(a) C[Ii + a]
        bool eee = 0;
        while (Counta < C.size())
        {
            if (CIiStartPlus(Counta) == '"')
            {
                if (init)
                {
                    Tempi = SplitPath_FileNAme(TempsStr);
                    eee = This->Bifton(Tempi->Directory, Tempi->FileName, print, SHA);
                    ret = (ret == 1) ? eee : ret;
                    // cout<<current_path()<<" <> "<<Tempi->Directory<<" -> "<<exists(get_c_name(Tempi->FileName))<<" "<<get_c_name(Tempi->FileName)<<endl;
                    if (exists(Tempi->Directory + get_c_name(Tempi->FileName)))
                    {
                        eee = This->Bifton(Tempi->Directory, get_c_name(Tempi->FileName), print, SHA);
                        ret = (ret == 1) ? eee : ret;
                    }
                    Counta = C.size();
                }
                else
                    init = 1;
            }
            else if (init)
                TempsStr.push_back(CIiStartPlus(Counta));
            Counta++;
        }
    }
    return ret;
}
string Deterministix::get_ALL_LinkageSwitch(char Separator)
{
    string ret = "";
    for (map<string, string>::iterator it = I2SL.begin(); it != I2SL.end(); it.operator++())
        if (this->I2SLB[it->first])
            ret.append(it->second) += Separator;
    ret.pop_back();
    return ret;
}
bool AlreadyIn(Deterministix *This, string P)
{
    bool ret = 0;
    for (int i = 0; i < This->CodePath.size(); i++)
        ret = (strcmp(This->CodePath[i].c_str(), P.c_str()) == 0) ? 1 : ret;
    if (!ret)
        for (int i = 0; i < This->objPath.size(); i++)
            ret = (strcmp(This->objPath[i].c_str(), P.c_str()) == 0) ? 1 : ret;
    return ret;
}
void Deterministix::print()
{

    for (map<string, string>::iterator it = I2SL.begin(); it != I2SL.end(); it.operator++())
        if (this->I2SLB[it->first])
            cout << "\t -> " << BOLDMAGENTA << it->second << GREEN << "(" << BOLDCYAN << it->first << GREEN << ")" << RESET << endl;
}
bool Exist(Deterministix *Al, string Out)
{
    for (int i = 0; i < Al->objPath.size(); i++)
    {
        if (strcmp(Al->objPath[i].c_str(), Out.c_str()) == 0)
            return 1;
    }
    return 0;
}
bool Deterministix::Bifton(string Path, string Filename, bool Print, bool SHA, bool ret)
{
    if (strcmp(Path.c_str(), "") == 0)
        Path = "./";
    #ifdef SHA1_HPP
    SHA1 Cyph = SHA1();
    #endif
    if (exists(Path))
    {

        stringstream ss;
        string EcPath = current_path();
        current_path(Path);
        string Cp = current_path();
        if (exists(Filename) && !Treated[Filename])
        {
            Treated[Filename] = 1;
            ifstream File(Filename);
            ss << File.rdbuf();
            if (Print)
                cout << getCurrentTime() << BOLDBLUE << " Analysing -> " << CYAN << Filename << RESET
                #ifdef SHA1_HPP
                #ifdef PRINTSHA1
                 << " ( " << YELLOW<< Cyph.from_file(Filename) << RESET << " ) "
                #endif
                #endif
                ;
            ret = FindIncludes(ss, this, Filename, Print, SHA);

            if (!AlreadyIn(this, Cp + '/' + get_c_name(Filename)))
            {
                string FP = get_c_name(Filename);
                // cout << FP << endl;
                //  cout<<FP<<(get_o_name(Filename)[get_o_name(Filename).size() - 1] == 'o')<<get_o_name(Filename)<<endl;
                if (exists(Cp + '/' + get_c_name(FP)))
                {
                    #ifdef SHA1_HPP
                    bool A = MatchSHA1File(Cp + "/." + FP + ".SHA1", Cp + '/' + get_c_name(FP));

                    bool B = 1;
                    if (exists(Cp + '/' + get_H_name(FP)))
                        B = MatchSHA1File(Cp + "/." + get_H_name(FP) + ".SHA1", Cp + '/' + get_H_name(FP));

                    if (A && B && ret && SHA && exists(Cp + '/' + get_o_name(FP)))
                    {

                        ret = 1;
                        CodePath.push_back("");
                    }
                    else
                    {
                    #endif
                    
                        ret = 0;
                        CodePath.push_back(Cp + '/' + FP);
                    #ifdef SHA1_HPP
                    }
                    #endif

                    objPath.push_back(Cp + '/' + FP);
                }
            }
            for (map<string, string>::iterator it = I2SL.begin(); it != I2SL.end(); it.operator++())
            {
                this->I2SLB[it->first] = (strstr(ss.str().c_str(), it->first.c_str())) ? 1 : this->I2SLB[it->first];
            }
        }
        else if (!Treated[Filename])
        {
            cout << getCurrentTime() << BOLDCYAN << " Error File: '" << RESET << RED << Filename << BOLDCYAN << "' Doesn't Exist! in " << current_path() << RESET << endl;
            // exit(0);
        }
        current_path(EcPath);
    }
    else if (strcmp(Path.c_str(), "") != 0)
    {

        cout << getCurrentTime() << BOLDCYAN << " Error Path: '" << RESET << RED << Path << BOLDCYAN << "' Doesn't Exist!" << endl;
        exit(0);
    }
    return ret;
}
Deterministix *Deterministix::Register(string Code, string linkageswitch)
{
    this->I2SL[Code] = linkageswitch,
    this->I2SLB[Code] = 0;
    return this;
}
