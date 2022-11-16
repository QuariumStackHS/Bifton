
#include "LibAsHeader/lah.hpp"
#include <bit>
#include <fstream>

size_t TopOfStack;

#define Bits 384
double
Matching (string K, string J)
{
  double Hits = 0;
  for (int l = 0; l < K.size (); l++)
    Hits = (K[l] != '=') ? (K[l] == J[l]) ? Hits + 1 : Hits : Hits;
  return Hits / K.size () * 100;
}
class CLa
{
public:
  CLa (int x) { assert (x == 0) isNOTfatal (x = 0); }
};
int
GetStackUsage ()
{
  int x;
  return (TopOfStack - (unsigned long long)&x);
}
double
StackLeft ()
{
  // cout<<rl.rlim_max<<" "<<GetStackUsage()<<endl;
  return GetStackUsage () - rl.rlim_max;
}
long
IterationsPerAmountsOfSeconds (long AOS, void (*Fnc) ())
{
  assert (AOS > 0) isfatal;
  long As = time (NULL), It = 0;
  while (As + AOS != time (NULL))
    Fnc (), It++;
  return It;
}
long long
MaxStack ()
{
  rlim_t kStackSize = 60 * 1024 * 1024;
  assert (0 == getrlimit (RLIMIT_STACK, &rl));
  isNOTfatal (assert (rl.rlim_cur < kStackSize) isfatal);
  rl.rlim_cur = kStackSize;
  // TraceVal (rl.rlim_cur);
  while (0 != setrlimit (RLIMIT_STACK, &rl))
    {
      assert (0 == setrlimit (RLIMIT_STACK, &rl)) isNOTfatal (kStackSize--;);
    }
  return kStackSize;
}
void
SetStackLimit (int MB)
{
  const rlim_t kStackSize = MB * 1024 * 1024;
  assert (0 == getrlimit (RLIMIT_STACK, &rl))
      isNOTfatal (assert (rl.rlim_cur < kStackSize) isfatal);
  rl.rlim_cur = kStackSize;
  // TraceVal (rl.rlim_cur);
  assert (0 == setrlimit (RLIMIT_STACK, &rl)) isfatal;
}

string
randomString (int charnbr)
{
  // DebugBreakPoint;
  string K = "";
  for (int i = 0; i < charnbr; i++)
    K.push_back (random () % 127 + 1);
  return K;
}
void
R ()
{
  String RS = randomString (32);
  RS.Hash ();
}

/*const double Hashpersec(int timea = 3, int inputSize = Bits)
{
    int iterations = 0;
    vector<String> Matrix;
    int outputsize = Hash1k().size();
    string r = randomString(inputSize);
    for (int i = 0; i < 22546675; i++)
        Matrix.push_back(r);
    for (time_t As = time(NULL), ntimes = As, last = ntimes; As + timea >
time(NULL); iterations++, ntimes = time(NULL))
    {
        if (iterations != Matrix.size())
            Hash1k(Matrix[iterations]);
    }
    return iterations / (timea - 1) / .40;
}*/
void
N ()
{
  // cout<<(GetStackUsage()rl.rlim_cur)<<endl;

  if (GetStackUsage () < rl.rlim_max / 2)
    {
      N ();
      // cout << (double)StackLeft() << endl;
    }
  return;
}
void
GGET ()
{
  GlobalInit (string *, STR_tias);
  cout << *STR_tias << endl;
}
double
VGet (double a)
{
  if (GetStackUsage () * 3 > rl.rlim_max)
    return -1;
  return 6 + ((a + 2) * (a + 2)) / VGet (a + 2);
}
double
pi ()
{
  return 3 + 1 / VGet (-3);
}
int
main ()
{
  srand (time (NULL));
  int iterations = 1;
  TopOfStack = (size_t)&iterations;
  String STR_tias = string ("Lol"); // randomString(65535);
  ofstream TestAct ("TA");
  TestAct << ((String)randomString (65535 * 0.749989 - 1)).b64encode ()
          << endl;
  cout << STR_tias.b64encode () << MaxStack () << endl;

  // string *Undefinedthing;
  // GlobalGet(Undefinedthing)
  GlobalSet (STR_tias);
  GlobalSet (TopOfStack);
  GlobalDestroy (TopOfStack);
  cout << GlobalExist (TopOfStack) << endl;
  FncSet (GGET);
  cout << GetStackUsage () << endl;

  SetStackLimit (62);
  int timea = 2;
  int HPS = IterationsPerAmountsOfSeconds (timea, &R) / timea;
  GGET ();
  string Ka = ".";
  for (int i = 0; i < GlobalsDetails.size (); i++)
    {
      cout << GlobalsDetails[i]._Name << " " << GlobalsDetails[i]._From
           << endl;
      for (int j = 0; j < WhoCalledGlobal[GlobalsDetails[i]._Name].size ();
           j++)
        {
          cout << "\t" << WhoCalledGlobal[GlobalsDetails[i]._Name][j] << endl;
        }
    }
  cout << setprecision (15) <<1/0.3183098861837906912<<" "<< (double)pi () << endl;
  // cout << HPS << endl;
  //  cout << Matching(Hash1k("um mot de passe"), Hash1k("un mot de passe?"))
  //  << "% of match" << endl; cout << IterationsPerAmountsOfSeconds(1, &R) <<
  //  endl;
}