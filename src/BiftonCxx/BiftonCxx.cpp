#include "BiftonCxx.hpp"

#include "Data/Registry.hpp"
string FMP(string g) { return string("<") + g + string(">"); }
Deterministix::Deterministix()
{
    RegisterDet(this);
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
void FindIncludes(stringstream &FileContain, Deterministix *This, string Filename, bool print = 0)
{

    string C = FileContain.str();
    string Tofind = "#include";
    vector<int> Includes;
    int Count = 0;
    bool Skip = 0;
    bool OneLineSkip = 0;
    int IncludesINT = 0;
    // if()
    for (int i = 0; i < C.size(); i++)
    {
        if ((C[i] == '"') || ((C[i] == '/') && (C[i + 1] == '*')) || ((C[i] == '*') && (C[i + 1] == '/')))
            Skip = !Skip;
        if ((C[i] == '/') && (C[i + 1] == '/'))
            OneLineSkip = 1;
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
                    Includes.push_back(i);
                else
                    IncludesINT--;
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
    for (int i = 0; i < IncludesINT; i++)
    {
        cout << ".";
    }
    if (print)
        cout << GREEN " Done √" << endl;
    for (int i = 0; i < Includes.size(); i++)
    {
        init = 0;
        Counta = 0;
        TempsStr = "";
#define Ii Includes[i]
#define CIiStartPlus(a) C[Ii + a]
        while (Counta < C.size())
        {
            if (CIiStartPlus(Counta) == '"')
            {
                if (init)
                {
                    Tempi = SplitPath_FileNAme(TempsStr);
                    This->Bifton(Tempi->Directory, Tempi->FileName, print);
                    // cout<<current_path()<<" <> "<<Tempi->Directory<<" -> "<<exists(get_c_name(Tempi->FileName))<<" "<<get_c_name(Tempi->FileName)<<endl;
                    if (exists(Tempi->Directory + get_c_name(Tempi->FileName)))
                        This->Bifton(Tempi->Directory, get_c_name(Tempi->FileName), print);
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
    return ret;
}
void Deterministix::print()
{
    for (int i = 0; i < this->CodePath.size(); i++)
        cout << YELLOW << "Used File: " << BOLDMAGENTA << GetFName(CodePath[i]) << RESET << endl;
    for (map<string, string>::iterator it = I2SL.begin(); it != I2SL.end(); it.operator++())
        if (this->I2SLB[it->first])
            cout << "\t-> " << BOLDMAGENTA << it->second << GREEN << "(" << BOLDCYAN << it->first << GREEN << ")" << RESET << endl;
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
void Deterministix::Bifton(string Path, string Filename, bool Print)
{
    if (strcmp(Path.c_str(), "") == 0)
        Path = "./";
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
                cout << BOLDBLUE << "Analysing -> " << CYAN << Filename;
            FindIncludes(ss, this, Filename, Print);

            if (!AlreadyIn(this, Cp + '/' + get_c_name(Filename)))
            {
                string FP = get_c_name(Filename);
                // cout << FP << endl;
                //  cout<<FP<<(get_o_name(Filename)[get_o_name(Filename).size() - 1] == 'o')<<get_o_name(Filename)<<endl;
                if (exists(Cp + '/' + get_c_name(FP)))
                    CodePath.push_back(Cp + '/' + FP);
                if (!Exist(this, get_o_name(FP)))
                    objPath.push_back(Cp + '/' + get_o_name(FP));
            }
            for (map<string, string>::iterator it = I2SL.begin(); it != I2SL.end(); it.operator++())
            {

                this->I2SLB[it->first] = (strstr(ss.str().c_str(), it->first.c_str())) ? 1 : this->I2SLB[it->first];
            }
        }
        else if (!Treated[Filename])
        {
            cout << BOLDCYAN << "Error File: '" << RESET << RED << Filename << BOLDCYAN << "' Doesn't Exist! in " << current_path() << RESET << endl;
            exit(0);
        }
        current_path(EcPath);
    }
    else if (strcmp(Path.c_str(), "") != 0)
    {

        cout << BOLDCYAN << "Error Path: '" << RESET << RED << Path << BOLDCYAN << "' Doesn't Exist!" << endl;
        exit(0);
    }
}
void Deterministix::Register(string Code, string linkageswitch)
{
    this->I2SL[Code] = linkageswitch,
    this->I2SLB[Code] = 0;
}
