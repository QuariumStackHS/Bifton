

#include <string>
#include <math.h>
#include <fstream>
#include <filesystem>
#include <sstream>
#include <iostream>
#include "./SHA1/SHA1.hpp"
#include <vector>
using namespace std;
#define MINP 40
#define MAXP 63
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
    inline RSA()
    {
        p = GenPrime(powl(2, MAXP), powl(2, MINP));
        q = GenPrime(powl(2, MAXP), powl(2, MINP));
        n = p * q;                                      //
        e = GenPrime(powl(2, MINP), powl(2, MINP / 2)); //
        phi = (p - 1) * (q - 1);
        d = fmod(1 / e, phi); //
    }
    inline RSA(double ec, long long nc)
    {
        this->e = ec;
        this->n = nc;
    }
    inline RSA(string filename)
    {
        ifstream FK(filename + ".VSig");
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
    vector<double> *Sign(string k)
    {
        vector<double> *Signature = new vector<double>();
        for (int i = 0; i < k.size(); i++)
        {
            Signature->push_back(fmod(pow(k[i], d), n));
        }
        return Signature;
    }
    bool VerifySig(string filename)
    {
        if (exists(filename + ".sig") == 0)
            return 0;
        ifstream PUK(filename + ".sig");
        ifstream PsK(filename + ".VSig");

        stringstream ss;
        stringstream ss2;
        ss2 << PsK.rdbuf();
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

        return (isValide(Signature, SHA1::from_file(filename)) && exists(filename + ".sig"));
    }
    void SaveSig(string filename)
    {
        ofstream PRK(filename + ".PCert");
        ofstream PUK(filename + ".VSig");
        ofstream PUKs(filename + ".Sig");
        PRK << "" << double2longlong(this->d) << ";" << double2longlong(e) << ";" << n << ";";
        PUK << "" << double2longlong(e) << ";" << n << ";";
        vector<double> *Signature = Sign(SHA1::from_file(filename));
        for (int i = 0; i < Signature->size(); i++)
            PUKs << double2longlong(Signature->at(i)) << ";";
    }

    bool isValide(vector<double> *Signature, string k)
    {
        if (Signature->size() != 0)
        {
            for (int i = 0; i < k.size(); i++)
                if (!IS)
                    return 0;
            return 1;
        }
        else
            return 0;
    }
    long long p, q, phi, n;
    double d, e;
};
/**
 * Given a string, this function will encode it in 64b (with padding)
 */

