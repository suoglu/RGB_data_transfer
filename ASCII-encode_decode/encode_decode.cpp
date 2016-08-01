 //  Yigit Suoglu Jul 28, 2016
// Encode and decode ASCII between char and bool array

#include "encode_decode.h"


void encodeASCII(char in, bool & out0, bool & out1, bool & out2, bool & out3, bool & out4, bool & out5, bool & out6, bool & out7)
{
   out0=0;
   out1=0;
   out2=0;
   out3=0;
   out4=0;
   out5=0;
   out6=0;
   out7=0;
   
   // int in = inC;
    if(in % 2)
        out7 = 1;
    in = in / 2;
    if(in % 2)
        out6 = 1;
    in = in / 2;
    if(in % 2)
        out5 = 1;
    in = in / 2;
    if(in % 2)
        out4 = 1;
    in = in / 2;
    if(in % 2)
        out3 = 1;
    in = in / 2;
    if(in % 2)
        out2 = 1;
    in = in / 2;
    if(in % 2)
        out1 = 1;
    in = in / 2;
    
    
    

}

char decodeASCII(bool in0, bool in1, bool in2, bool in3, bool in4, bool in5, bool in6, bool in7)
{
    
    bool in[8];
    in[0] = in0;
    in[1] = in1;
    in[2] = in2;
    in[3] = in3;
    in[4] = in4;
    in[5] = in5;
    in[6] = in6;
    in[7] = in7;
    
    int out = 0;
    for(int j = 1; j < 8; j++)
    {
        out = out * 2;
        if(in[j])
            out = out + 1;
    }
    return (char) out;
}

