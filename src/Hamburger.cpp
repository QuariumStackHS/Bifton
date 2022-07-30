#include <iostream>
#include <string>
#include <vector>
using namespace std;
/*
0000 0001 0010 0011
0100 0101 0110 0111
1000 1101 1110 1111

*/

#define BLOCK vector<bool>
BLOCK *B_Str(string k)
{
    BLOCK *BRet = new BLOCK();
    for (u_int64_t i = 0; i < k.size(); BRet->push_back(k[i] - 48), i++)
        ;
    return BRet;
}
class Block
{

public:
    bool ISParity(u_int64_t Size)
    {
        bool R;
        // cout<<Size<<" ; "<<Parity.size()<<endl;
        for (u_int64_t i = 0; i < Parity.size(); i++)
            if (Parity[i] == Size)
            {
                /*cout<<Parity[i]<<endl;*/ return 1;
            }
        return 0;
    }
    BLOCK *block = new BLOCK();
    vector<u_int64_t> Parity;
    u_int64_t Block_Pou_int64_ter = 0;
    u_int64_t EXP(u_int64_t N, u_int64_t E)
    {
        u_int64_t A = 1;
        for (u_int64_t i = 0; i < E; i++)
            Parity.push_back(A), A *= N;
        for (u_int64_t i = 0; i < A; i++)
            block->push_back(0);
        cout << A << " " << block->size() << endl;
        return A;
    }
    u_int64_t Set_block(BLOCK *Bl0ck)
    {
        for (u_int64_t i = 0; i < Bl0ck->size(); i++)
            Set(Bl0ck->at(i)) /*, cout << Bl0ck->at(i)*/;
        return this->Block_Pou_int64_ter;
    }
    Block(u_int64_t exp)
    {
        EXP(2, exp);
    }
    Block operator<<(bool Data)
    {
        Set(Data);
        return *this;
    }
    u_int64_t Set(bool A)
    {
        if (this->ISParity(Block_Pou_int64_ter))
            block->at(Block_Pou_int64_ter) = 1, cout << "Parity" << endl;
        // cout<<(Block_Pou_int64_ter<S)<<endl;
        // cout<<A<<endl;
        else if (this->ISParity(Block_Pou_int64_ter))
        {
            block->at(Block_Pou_int64_ter) = 1;
             Block_Pou_int64_ter++;
            cout << "Parity" << endl;
        }
        else
            block->at(Block_Pou_int64_ter) = A;
        Block_Pou_int64_ter++;
        return Block_Pou_int64_ter;
    }
};

int Fast_8_Bits = 8;
int Slow_16_Bits = 16;
int Slower_32_Bits = 32;
int Very_Slow_40_bits = 40;

int main()
{
    Block F(26);
    F.Set_block(B_Str("10101010101010101"));
    //F.Set(1);
    for (u_int64_t i = 0; i < F.Block_Pou_int64_ter; i++)
        cout << F.block->at(i);
    cout << endl;
    for (u_int64_t i = 0; i < F.Block_Pou_int64_ter; i++)
        cout << F.ISParity(i);
}