 //  Yigit Suoglu Jul 28, 2016
// Encode and decode ASCII between char and bool array

#include "encode_decode.h"


void encodeASCII(char in, bool out[8])
{
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

