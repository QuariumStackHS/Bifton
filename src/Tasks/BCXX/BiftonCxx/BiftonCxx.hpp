#ifndef BIFTONCXX_HPP
#define BIFTONCXX_HPP

#include "Data/ComputerInfo.h"
#include <ctime>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <vector>

#define RESET "\033[0m"
#define BLACK "\033[30m"	
#define RED "\033[31m"
#define GREEN "\033[32m"	
#define YELLOW "\033[33m"		
#define BLUE "\033[34m"	
#define MAGENTA "\033[35m"			
#define CYAN "\033[36m"	
#define WHITE "\033[37m"	
#define BOLDBLACK "\033[1m\033[30m"	 
#define BOLDRED "\033[1m\033[31m"	 
#define BOLDGREEN "\033[1m\033[32m"	 
#define BOLDYELLOW "\033[1m\033[33m"  
#define BOLDBLUE "\033[1m\033[34m"	  
#define BOLDMAGENTA "\033[1m\033[35m" 
#define BOLDCYAN "\033[1m\033[36m"	  
#define BOLDWHITE "\033[1m\033[37m"	 
#define RESET "\033[0m"
#define BLACK "\033[30m" 
#define RED "\033[31m"
#define GREEN "\033[32m" 
#define YELLOW "\033[33m" 
#define BLUE "\033[34m"	
#define MAGENTA "\033[35m" 
#define CYAN "\033[36m"
using namespace std;
using namespace filesystem;
string FMP(string);
string FMS(string);
inline std::ifstream::pos_type filesize(const char *filename)
{
	std::ifstream in(filename, std::ifstream::ate | std::ifstream::binary);
	return in.tellg();
}
inline void ShowBand(string Var)
{
	cout << "\t ";
	for (int i = 0; i < 20 - (Var.size() - 1); i++)
		cout << RED << "═";
	cout << BOLDGREEN << Var << RESET;
	for (int i = 0; i < 20 - (Var.size() - 1); i++)
		cout << RED << "═" << RESET;
	cout << endl;
}
inline void SplitPATHSFromCommand(string *Path, string *file, string *eArg)
{
	for (int i = 0; (eArg->at(i) != (':')) && (i != eArg->size()); i++)
	{
		Path->push_back(eArg->at(i));
	}
	for (int i = Path->size() + 1; i < eArg->size(); i++)
	{
		file->push_back(eArg->at(i));
	}
}
inline void replace(string &input, const string &from, const string &to)
{
	auto pos = 0;
	while (true)
	{
		size_t startPosition = input.find(from, pos);
		if (startPosition == string::npos)
			return;
		input.replace(startPosition, from.length(), to);
		pos += to.length();
	}
}
inline string get_c_name(string name)
{
	string ret = name;
	replace(ret, ".h", ".c");
	return ret;
}
inline string get_H_name(string name)
{
	string ret = name;
	replace(ret, ".c", ".h");
	return ret;
}
string getCurrentTime();
inline string get_o_name(string name)
{
	string ret = name;
	replace(ret, ".cpp", ".o");
	replace(ret, ".c", ".o");
	return ret;
}
inline int OUTPUTTYPE='E';
inline string get_E_name(string name)
{

	string ret = name;
	switch (OUTPUTTYPE)
	{
	case 'E':
		replace(ret, ".cpp", "");
		replace(ret, ".c", "");
		break;
	case 'L':
		replace(ret, ".cpp", ".a");
		replace(ret, ".c", ".a");
		break;
	case 'D':
		replace(ret, ".cpp", ".so");
		replace(ret, ".c", ".so");

		default:
		break;
	}

	return ret;
}
inline string get_S_name(string name)
{
	string ret = name;
	replace(ret, ".cpp", ".s");
	replace(ret, ".c", ".s");
	return ret;
}
class Deterministix
{
protected:
	map<string, string> I2SL; 
	map<string, bool> I2SLB;
	map<string, bool> Treated;
	map<string, string> C2SC;
	map<string, bool> C2SB;

public:
	int AnalysedFiles = 0;
	int LineAprox = 0;
	int RealLine = 0;
	vector<string> CodePath;
	vector<string> objPath;
	Deterministix();
	Deterministix *Register(string, string);
	void print();
	string get_ALL_LinkageSwitch(char Separator);
	bool Bifton(string, string, bool Print = 0, bool SHA = 1, bool ret = 1);
};

class Sizer
{
public:
	inline Sizer(char C, float Data) { this->c = C, this->data = Data; }
	char c;
	float data;
};
string GetFName(string path);
inline Sizer sizetoK(float bytes, int Base = 1000)
{
	float kilobyte = Base;
	float megabyte = kilobyte * Base;
	float gigabyte = megabyte * Base;
	float terabyte = gigabyte * Base;
	if ((bytes >= kilobyte) && (bytes < megabyte))
	{
		return Sizer('K', bytes / kilobyte);
	}
	else if ((bytes >= megabyte) && (bytes < gigabyte))
	{
		return Sizer('M', bytes / megabyte);
	}
	else if ((bytes >= gigabyte) && (bytes < terabyte))
	{
		return Sizer('G', bytes / gigabyte);
	}
	else if (bytes >= terabyte)
	{
		return Sizer('T', bytes / terabyte);
	}
	else
	{
		return Sizer('\0', bytes);
	}
}
#endif