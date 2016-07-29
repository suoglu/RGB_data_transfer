 // Yigit Suoglu Jul 29, 2016
// Header for rgb detection code (from given threshold values)

#ifndef RGB__Detection_h
#define RGB__Detection_h

#include "colorBit_Struct.h"

void detect_rgb(uint16_t r, uint16_t g, uint16_t b, colorBit th_Val[8], bool & r_on, bool & g_on, bool & b_on);

#endif /* RGB__Detection_h */
