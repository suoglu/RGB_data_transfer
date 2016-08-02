 // Owner: Onur Calik, edited by Yigit Suoglu
// Contains code for 8 4 Hamming error correction medhod. Works with boolean values
//#include <iostream>
//#include <string>
#include "HammingCode.h"

using namespace std;
/*
void addParity(bool d1, bool d2, bool d3, bool d4, bool d5, bool d6, bool d7, bool d8, bool & p1, bool & p2, bool & p4, bool & p8);
void checkParity(bool &d1, bool &d2, bool &d3, bool &d4, bool &d5, bool &d6, bool &d7, bool &d8, bool & p1, bool & p2, bool & p4, bool & p8, bool & err); */ //for use at testing without header file
/*
int main(){
	
	bool p1,p2,p4,p8,d1=1,d2=1,d3=0,d4=0,d5=0,d6=1,d7=0,d8=0;
	addParity(d1,d2,d3,d4,d5,d6,d7,d8,p1,p2,p4,p8);
	checkParity(d1,d2,d3,d4,d5,d6,d7,d8,p1,p2,p4,p8);
	return 0;
}*/ //for testing




void addParity(bool d1, bool d2, bool d3, bool d4, bool d5, bool d6, bool d7, bool d8, bool & p1, bool & p2, bool & p4, bool & p8)
// Give your data to dx's and give containers for parity bits to px's (referance)
{
	
	p1=d1^d2^d4^d5^d7;
	p2=d1^d3^d4^d6^d7;
	p4=d2^d3^d4^d8;
	p8=d5^d6^d7^d8;
/*
	cout<<p1;
	cout<<p2;
	cout<<p4;
	cout<<p8;
  //sentData={p1,p2,d1,p4,d2,d3,d4,p8,d5,d6,d7,d8};
*/ //for testing
	
	
}

void checkParity(bool &d1, bool &d2, bool &d3, bool &d4, bool &d5, bool &d6, bool &d7, bool &d8, bool & p1, bool & p2, bool & p4, bool & p8, bool & err)
// Give data to dx's and px's (both referance) also returns err for error feedback
{
	bool bits[] = {p1,p2,d1,p4,d2,d3,d4,p8,d5,d6,d7,d8};
    
	bool r1 = p1 ^ d1 ^ d2 ^ d4 ^ d5 ^ d7;
	bool r2 = p2 ^ d1 ^ d3 ^ d4 ^ d6 ^ d7;
	bool r3 = p4 ^ d2 ^ d3 ^ d4 ^ d8;
	bool r4 = p8 ^ d5 ^ d6 ^ d7 ^ d8;
   /*
    cout << r1;
	cout << r2;
	cout << r3;
	cout << r4;
	*/ //for testing
    
    
	if (r1 | r2 | r3 | r4)
    {
        int hataliBit=r1+2*r2+4*r3+8*r4 - 1;
		bits[hataliBit] = !bits[hataliBit];
        err = true;
    }
    else
    {
	/*	
     cout << "\nNo error!\n"; */ //for testing
        err = false;
	}
    
    p1 = bits[0];
    p2 = bits[1];
    d1 = bits[2];
    p4 = bits[3];
    d2 = bits[4];
    d3 = bits[5];
    d4 = bits[6];
    p8 = bits[7];
    d5 = bits[8];
    d6 = bits[9];
    d7 = bits[10];
    d8 = bits[11];
    
}
