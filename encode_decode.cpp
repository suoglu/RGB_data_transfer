 //  Yigit Suoglu Jul 28, 2016
// Encode and decode ASCII between char and bool array

#include "encode_decode.h"


void encodeASCII(char in, bool out0, bool out1, bool out2, bool out3, bool out4, bool out5, bool out6, bool out7)
{
   bool out[8];
   out[0] = out0;
   out[1] = out1;
   out[2] = out2;
   out[3] = out3;
   out[4] = out4;
   out[5] = out5;
   out[6] = out6;
   out[7] = out7;
   
    for(int j = 0; j < 8; j++)
        out[j] = 0;
    
   // int in = inC;
    out[0] = 0;
    if(in % 2)
        out[7] = 1;
    in = in / 2;
    if(in % 2)
        out[6] = 1;
    in = in / 2;
    if(in % 2)
        out[5] = 1;
    in = in / 2;
    if(in % 2)
        out[4] = 1;
    in = in / 2;
    if(in % 2)
        out[3] = 1;
    in = in / 2;
    if(in % 2)
        out[2] = 1;
    in = in / 2;
    if(in % 2)
        out[1] = 1;
    in = in / 2;
}

char decodeASCII(bool in[8])
{
    int out = 0;
    for(int j = 1; j < 8; j++)
    {
        out = out * 2;
        if(in[j])
            out = out + 1;
    }
    return (char) out;
}

