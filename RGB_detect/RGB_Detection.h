 // Yigit Suoglu Jul 29, 2016
// Header for rgb detection code (from given threshold values)

#ifndef RGB_Detection_h
#define RGB_Detection_h

#include "colorBit_Struct.h"

void detect_rgb(unsigned short r, unsigned short g, unsigned short b, colorBit th_Val[8], bool & r_on, bool & g_on, bool & b_on);

#endif /* RGB_Detection_h */
