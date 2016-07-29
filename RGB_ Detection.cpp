 // Yigit Suoglu Jul 29, 2016
// includes code detects from given threshold values and enviorement RGB values

#include "RGB_ Detection.h"

void detect_rgb(uint16_t r, uint16_t g, uint16_t b, colorBit th_Val[8], bool & r_on, bool & g_on, bool & b_on)
{
	if((r > th_Val[7].r_t) & (g > th_Val[7].g_t) & (b > th_Val[7].b_t)) // RGB HIGH
	{
		r_on = g_on = b_on = 1;
		return;
	}
	if((r < th_Val[6].r_t) & (g > th_Val[6].g_t) & (b > th_Val[6].b_t)) // GB HIGH
	{
		g_on = b_on = 1;
		r_on = 0;
		return;
	}
	if((r > th_Val[5].r_t) & (g < th_Val[5].g_t) & (b > th_Val[5].b_t)) // RB HIGH
	{
		r_on = b_on = 1;
		g_on = 0;
		return;
	}
	if((r > th_Val[4].r_t) & (g > th_Val[4].g_t) & (b < th_Val[4].b_t)) // RG HIGH
	{
		r_on = g_on = 1;
		b_on = 0;
		return;
	}
	if(b > th_Val[3].b_t) // B HIGH
	{
		b_on = 1;
		r_on = g_on = 0;
		return;
	}
	if(g > th_Val[2].g_t) // G HIGH
	{
		r_on = b_on = 0;
		g_on = 1;
		return;
	}
	if(r > th_Val[1].r_t) //R HIGH
	{
		r_on = 1;
		g_on = b_on = 0;
		return;
	}
	r_on = g_on = b_on = 0; //NULL
}