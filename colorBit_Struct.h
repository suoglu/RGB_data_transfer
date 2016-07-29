 // Yigit Suoglu Jul 29, 2016
// structure for tresholds

#ifndef colorBit_Struct_h
#define colorBit_Struct_h

/*typedef*/ struct colorBit{
    bool bits[3]; //Signal code (RGB)
    uint16_t r_t, g_t, b_t; //R G B threshold values
};

#endif /* colorBit_Struct_h */
