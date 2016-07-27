//
//  HammingCode.h
//  testbanch
//
//  Created by Yigit Suoglu on 28/07/16.
//  Copyright © 2016 Yigit Suoglu. All rights reserved.
//

#ifndef HammingCode_h
#define HammingCode_h


void addParity(bool d1, bool d2, bool d3, bool d4, bool d5, bool d6, bool d7, bool d8, bool & p1, bool & p2, bool & p4, bool & p8);
void checkParity(bool &d1, bool &d2, bool &d3, bool &d4, bool &d5, bool &d6, bool &d7, bool &d8, bool & p1, bool & p2, bool & p4, bool & p8, bool & err);


#endif /* HammingCode_h */
