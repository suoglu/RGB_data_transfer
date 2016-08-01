//
//  TransmitCom.h
//  testbanch
//
//  Created by Yigit Suoglu on 01/08/16.
//  Copyright © 2016 Yigit Suoglu. All rights reserved.
//

#ifndef TransmitCom_h
#define TransmitCom_h

void flashSequence(char sequence, uint16_t ered, uint16_t  egreen, uint16_t eblue);
void flashDotOrDash(int color, bool dotOrDash);
void synchronization(int initDelay);


#endif /* TransmitCom_h */
