
#include <iostream>
#include <algorithm>
#include <math.h>
#include <random>
#include <string.h>
#include <cstring>
#include <type_traits>
#ifdef assert
#undef assert
#endif
#pragma startup BeforeMain
void BeforeMain();
namespace LAH
{
using namespace std;
string cuttree (string K);
#ifndef __DOESQUIT
#define __DOESQUIT
inline int DIDASSERTFAILED = 0;
#define Debug
#endif
#define isfatal                                                               \
  ;                                                                           \
  DIDASSERTFAILED ? exit (DIDASSERTFAILED) : void (0);
#define assert(BOOLEAN)                                                       \
  DIDASSERTFAILED = 0;                                                        \
  if (BOOLEAN == 0)                                                           \
    cout << "Assertion failed: " << #BOOLEAN << ", line " << __LINE__         \
         << ", function " << __func__ << " inside file "                      \
         << cuttree (__FILE__) << endl,                                       \
        DIDASSERTFAILED = true;
#define isNOTfatal(Solution)                                                  \
  ;                                                                           \
  if (DIDASSERTFAILED)                                                        \
  cout << "Not Fatal trying: " << #Solution << endl, Solution
};
#include <bit>
#include <map>
inline struct rlimit rl;
inline struct rusage ru;
void SetStackLimit (int MB);

using namespace std;

using namespace LAH;
#define Trace cout << cuttree (__FILE__) << "@" << __LINE__ << endl;
#define TraceVal(Val)                                                         \
  cout << cuttree (__FILE__) << "@" << __LINE__ << " --> \"" << #Val          \
       << "\" >-> " << (Val) << endl;

inline map<string, unsigned long long> Globals;

struct GlobalPTRDetails
{
  string _From;
  string _Name;
};
inline vector<GlobalPTRDetails> GlobalsDetails; // detail like name and from
inline map<string, void (*) ()> Fncs;
inline map<string, vector<string> > WhoCalledGlobal;
#define FncSet(Fname) Fncs[#Fname] = &Fname
#define FncGet(Fname)                                                         \
  assert ((*Fncs[#Fname]) != 0) isfatal;                                      \
  (*Fncs[#Fname])
inline struct GlobalPTRDetails GPTRD;
#define GlobalExist(Name) (Globals[#Name]!=0)
#define GlobalDestroy(Name) Globals[#Name] = 0;
#define GlobalSet(Name)                                                       \
  Globals[#Name] = (unsigned long long)&Name;                                 \
  GPTRD._From = string (__FILE__)                                             \
                    .append ("@")                                             \
                    .append (to_string (__LINE__))                            \
                    .append (">->")                                           \
                    .append (__func__);                                       \
  GPTRD._Name = #Name;                                                        \
  GlobalsDetails.push_back (GPTRD);
#define GlobalGet(Name)                                                       \
  assert (Globals[#Name] != 0) isfatal;                                       \
  (decltype (Name)) Globals[#Name];                                           \
  WhoCalledGlobal[#Name].push_back (__func__);
#define GlobalInit(Type, Name)                                                \
  assert (Globals[#Name] != 0) isfatal;                                       \
  Type Name = (Type)Globals[#Name];                                           \
  WhoCalledGlobal[#Name].push_back (__func__);
inline const char *B64chars
      = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

inline const int B64index[256]
      = { 0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
          0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
          0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  62, 63, 62, 62, 63,
          52, 53, 54, 55, 56, 57, 58, 59, 60, 61, 0,  0,  0,  0,  0,  0,
          0,  0,  1,  2,  3,  4,  5,  6,  7,  8,  9,  10, 11, 12, 13, 14,
          15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 0,  0,  0,  0,  63,
          0,  26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40,
          41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51 };
class String : public string
{
protected:
  

  inline const std::string
  b64encode (const void *data, const size_t &len)
  {
    std::string result ((len + 2) / 3 * 4, '=');
    unsigned char *p = (unsigned char *)data;
    char *str = &result[0];
    size_t j = 0, pad = len % 3;
    const size_t last = len - pad;

    for (size_t i = 0; i < last; i += 3)
      {
        int n = int (p[i]) << 16 | int (p[i + 1]) << 8 | p[i + 2];
        str[j++] = B64chars[n >> 18];
        str[j++] = B64chars[n >> 12 & 0x3F];
        str[j++] = B64chars[n >> 6 & 0x3F];
        str[j++] = B64chars[n & 0x3F];
      }
    if (pad)
      {
        int n = --pad ? int (p[last]) << 8 | p[last + 1] : p[last];
        str[j++] = B64chars[pad ? n >> 10 & 0x3F : n >> 2];
        str[j++] = B64chars[pad ? n >> 4 & 0x03F : n << 4 & 0x3F];
        str[j++] = pad ? B64chars[n << 2 & 0x3F] : '=';
      }
    return result;
  }

  inline const std::string
  b64decode (const void *data, const size_t &len)
  {
    if (len == 0)
      return "";

    unsigned char *p = (unsigned char *)data;
    size_t j = 0, pad1 = len % 4 || p[len - 1] == '=',
           pad2 = pad1 && (len % 4 > 2 || p[len - 2] != '=');
    const size_t last = (len - pad1) / 4 << 2;
    std::string result (last / 4 * 3 + pad1 + pad2, '\0');
    unsigned char *str = (unsigned char *)&result[0];

    for (size_t i = 0; i < last; i += 4)
      {
        int n = B64index[p[i]] << 18 | B64index[p[i + 1]] << 12
                | B64index[p[i + 2]] << 6 | B64index[p[i + 3]];
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
  String (string k) { this->append (k); }
  inline string
  Hash ()
  {
    string K = *this;
    int Bits = 96;
    int HashSize = Bits / 3;
    while (K.size () % (HashSize * 2) != 0)
      K.push_back (gcd (K.size (), HashSize * K[K.size () - 1]));
    String Hash = string (HashSize, -1);
    int ITNbr = K.size () / HashSize;
    char Pre = HashSize - 1;
    for (int runs = 0; runs < HashSize / 2; runs++)
      for (int i = 0, sum = 0; i < ITNbr; i++, sum += ITNbr * HashSize)
        for (int j = -1; j < HashSize;
             j++, sum += Pre = Hash[j]
                  ^= (K[i * ITNbr + j] ^ (sum + ITNbr * HashSize) >> Pre)
                     - (sum ^ Hash[j]) + j)
          ;
    return Hash.b64encode ();
    // return Hash1k(*this);
  }
  inline String
  b64encode ()
  {
    return b64encode (this->c_str (), this->size ());
  }
  inline String
  b64decode ()
  {
    return b64decode (this->c_str (), this->size ());
  }
};
