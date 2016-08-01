 //  Yigit Suoglu Jul 28, 2016
// Headers for same named cpp file 

#ifndef encode_decode_h
#define encode_decode_h


using namespace std;

void encodeASCII(char in, bool & out0, bool & out1, bool & out2, bool & out3, bool & out4, bool & out5, bool & out6, bool & out7); //bool out[8]
char decodeASCII(bool in0, bool in1, bool in2, bool in3, bool in4, bool in5, bool in6, bool in7);

#endif /* encode_decode_h */
