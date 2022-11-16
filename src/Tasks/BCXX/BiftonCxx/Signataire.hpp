

#include<string>
#include <cstring>
#include <math.h>
#include <fstream>
#include <filesystem>
#include <sstream>
#include <iostream>
#include "SHA1/SHA1.hpp"
#include <vector>
using namespace std;
#define MINP 32
#define MAXP 63
static const char *B64chars = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

static const int B64index[256] =
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
    if (pad)
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

std::string b64encode(const std::string &str)
{
    return b64encode(str.c_str(), str.size());
}

std::string b64decode(const std::string &str64)
{
    return b64decode(str64.c_str(), str64.size());
}

inline bool ends_with(std::string const &value, std::string const &ending)
{
    if (ending.size() > value.size())
        return false;
    return std::equal(ending.rbegin(), ending.rend(), value.rbegin());
}
#include <time.h>
using namespace std;
inline int gcd(int a, int b)
{
    int t;
    while (1)
    {
        t = a % b;
        if (t == 0)
            return b;
        a = b;
        b = t;
    }
}
inline double longlong2double(long long I)
{
    double *J;
    J = ((double *)&I);
    return *J;
}
inline long long double2longlong(double I)
{
    long long *J;
    J = ((long long *)&I);
    return *J;
}
inline bool IsPrime(int n)
{
    if (n == 2 || n == 3)
        return true;

    if (n <= 1 || n % 2 == 0 || n % 3 == 0)
        return false;

    for (int i = 5; i * i <= n; i += 6)
    {
        if (n % i == 0 || n % (i + 2) == 0)
            return false;
    }

    return true;
}

inline long long GenPrime(long long Max, long long Min)
{
    long long ans = 4;
    while (!IsPrime(ans))
        ans = rand() % Max + Min;
    return ans;
}
inline bool Dif1(double K, double i)
{
    if ((K - i < 1) && (K - i > -1))
        return 1;
    return 0;
}

class RSA
{
public:
    unsigned int n, phi;
    long double e, d;
    inline RSA()
    {
        int p = GenPrime(powl(2, MAXP), powl(2, MINP));
        int q = GenPrime(powl(2, MAXP), powl(2, MINP));
        n = p * q;
        e = GenPrime(powl(2, MINP), powl(2, MINP / 2));
        phi = (p - 1) * (q - 1);
        d = fmod(1 / e, phi);
    }
    inline RSA(double ec, unsigned long long nc)
    {
        this->e = ec;
        this->n = nc;
    }
    inline RSA(string filename)
    {
        ifstream FK(filename + ".RSAKey");
        stringstream ss;
        ss << FK.rdbuf();
        string sss = ss.str();
        string buffer = "";
        int ea = 0;
        for (int i = 0; i < sss.size(); i++)
        {
            if (sss[i] == ';')
            {
                if (0 == ea)
                    this->e = longlong2double(stoll(buffer));
                else
                    this->n = stoll(buffer);
                ea++;

                buffer = "";
            }
            else
                buffer.push_back(sss[i]);
        }
    }
#define IS Dif1(fmod(k[i], n), fmod(pow(Signature->at(i), e), n))
    string *Sign(string k)
    {
        string *Signature = new string();
        for (int i = 0; i < k.size(); i++)
        {
            Signature->push_back(fmod(pow(k[i], d), n));
        }
        return Signature;
    }
    bool VerifySig(string filename)
    {

        ifstream PUK(filename + ".Sig");

        stringstream ss;
        stringstream ss2;
        string sss2 = ss2.str();
        ss << PUK.rdbuf();
        string sss = ss.str();
        string buffer = "";

        vector<double> *Signature = new vector<double>();
        try
        {
            for (int i = 0; i < sss.size(); i++)
            {
                if (sss[i] == ';')
                {
                    Signature->push_back(longlong2double(stoll(buffer)));
                    buffer = "";
                }
                else
                    buffer.push_back(sss[i]);
            }
        }
        catch (...)
        {
        }

        return isValide(Signature, SHA1::from_file(filename));
    }
    void SaveSig(string filename)
    {
        ofstream PRK(filename + ".PCert");
        ofstream PUKs(filename + ".Sig");
        PRK << "" << double2longlong(this->d) << ";" << double2longlong(e) << ";" << n << ";";
        string *Signature = Sign(SHA1::from_file(filename));
        for (int i = 0; i < Signature->size(); i++)
            PUKs << double2longlong(Signature->at(i)) << ";";
    }

    bool isValide(vector<double> *Signature, string k)
    {
        if (Signature->size() != 0)
        {
            for (int i = 1; i < k.size(); i++)
            {
                if (!IS)
                    return 0;
                return 1;
            }
        }
        else
            return 0;
        return 0;
    }
};
