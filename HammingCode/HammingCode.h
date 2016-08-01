//  Yigit Suoglu Jul 28, 2016
// Headers for hamming codes written by Onur Calik

#ifndef HammingCode_h
#define HammingCode_h


void addParity(bool d1, bool d2, bool d3, bool d4, bool d5, bool d6, bool d7, bool d8, bool & p1, bool & p2, bool & p4, bool & p8);
void checkParity(bool &d1, bool &d2, bool &d3, bool &d4, bool &d5, bool &d6, bool &d7, bool &d8, bool & p1, bool & p2, bool & p4, bool & p8, bool & err);


#endif /* HammingCode_h */
