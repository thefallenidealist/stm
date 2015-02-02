#ifndef GLCD_HIGH_H
#define GLCD_HIGH_H

#include <stdint.h>
#include "glcd_colors.h"
#include "glcd_mid.h"
//#include "glcd_font.h" // .c

#define PORTRAIT	0
#define P1		0
#define LANDSCAPE	1
#define L1		1
#define P2		2
#define L2		3

#define CHAR_X	6	// how many pixels is wide char
#define CHAR_Y	6	// how many pixels is wide char
#define CHAR_SPACE	2	// empty space beetween chars

#ifndef vuint8
#define vuint8		volatile uint8_t
#endif

#ifndef vuint8_t
#define vuint8_t	volatile uint8_t
#endif

#ifndef vuint16
#define vuint16		volatile uint16_t
#endif

#ifndef vuint16_t
#define vuint16		volatile uint16_t
#define vuint16_t	volatile uint16_t
#endif

#ifndef vuint32
#define vuint32		volatile uint32_t
#endif

#ifndef vuint32_t
#define vuint32_t	volatile uint32_t
#endif


// prototipi
void glcd_setOrientation(char orientation);
void glcd_setX(uint16_t x0, uint16_t x1);
void glcd_setY(uint16_t y0, uint16_t y1);
void glcd_setXY(uint16_t x0, uint16_t x1, uint16_t y0, uint16_t y1);
void glcd_pixel(vuint16_t x0, vuint16_t y0, vuint16_t color);
void glcd_hline(uint16_t x0, uint16_t y0, uint16_t length, uint16_t color);
void glcd_vline(uint16_t x0, uint16_t y0, uint16_t length, uint16_t color);
void glcd_fillRectangle(vuint16_t x0, vuint16_t y0, vuint16_t length, vuint16_t width, vuint16_t color);
void glcd_bg(int color);
void glcd_char(unsigned char ascii, unsigned int x, unsigned int y, unsigned int size, unsigned int fgcolor);
void glcd_string(char *string, unsigned int x, unsigned int y, unsigned int size, unsigned int fgcolor);
//uint8_t glcd_number(unsigned int long_num,unsigned int x0, unsigned int y0,unsigned int size,unsigned int fgcolor);
uint8_t glcd_number(int32_t long_num, uint16_t x0, uint16_t y0, uint8_t size, uint16_t fgcolor);

#endif
